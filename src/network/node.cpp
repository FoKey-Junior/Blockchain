#include "network/node.h"
#include "core/crypto.h"

#include <filesystem>
#include <fstream>
#include <vector>
#include <cstring>
#include <sodium.h>

namespace fs = std::filesystem;

namespace network {

namespace {
constexpr std::uint32_t Magic = 0x424C434B; // BLCK
constexpr std::uint16_t Version = 1;

struct Header {
    std::uint32_t magic;
    std::uint16_t version;
    std::uint16_t reserved;
    core::AddressBytes sender;
    core::AddressBytes receiver;
    core::HashBytes hash;
    std::uint32_t name_len;
    std::uint32_t mime_len;
    std::uint32_t tx_len;
    std::uint64_t file_size;
};
} // namespace

Node::Node(std::string bind_host, std::uint16_t port, std::string storage_dir)
    : bind_host_(std::move(bind_host)),
      port_(port),
      storage_dir_(std::move(storage_dir)) {}

Node::~Node() {
    stop();
}

bool Node::start() {
    if (running_.exchange(true)) {
        return true;
    }
    worker_ = std::thread([this]() { accept_loop(); });
    return true;
}

void Node::stop() {
    if (!running_.exchange(false)) {
        return;
    }
    if (worker_.joinable()) {
        worker_.join();
    }
}

void Node::set_on_file_received(FileCallback cb) {
    on_file_received_ = std::move(cb);
}

bool Node::send_file(const std::string& host, std::uint16_t port,
                     const core::AddressBytes& sender,
                     const core::AddressBytes& receiver,
                     const std::string& path,
                     const core::FileMetadata& metadata,
                     core::HashBytes file_hash,
                     const std::vector<std::uint8_t>& tx_payload,
                     std::string& error) {
    try {
        asio::io_context io;
        asio::ip::tcp::resolver resolver(io);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        asio::ip::tcp::socket socket(io);
        asio::connect(socket, endpoints);

        Header header{};
        header.magic = Magic;
        header.version = Version;
        header.sender = sender;
        header.receiver = receiver;
        header.hash = file_hash;
        header.name_len = static_cast<std::uint32_t>(metadata.name.size());
        header.mime_len = static_cast<std::uint32_t>(metadata.mime.size());
        header.tx_len = static_cast<std::uint32_t>(tx_payload.size());
        header.file_size = metadata.size;

        std::vector<std::uint8_t> buffer;
        buffer.resize(sizeof(Header));
        std::memcpy(buffer.data(), &header, sizeof(Header));
        buffer.insert(buffer.end(), metadata.name.begin(), metadata.name.end());
        buffer.insert(buffer.end(), metadata.mime.begin(), metadata.mime.end());
        buffer.insert(buffer.end(), tx_payload.begin(), tx_payload.end());

        std::ifstream file(path, std::ios::binary);
        if (!file) {
            error = "Failed to open file";
            return false;
        }

        asio::write(socket, asio::buffer(buffer));

        constexpr std::size_t chunk = 64 * 1024;
        std::vector<char> file_buffer(chunk);
        while (file) {
            file.read(file_buffer.data(), static_cast<std::streamsize>(file_buffer.size()));
            auto count = file.gcount();
            if (count > 0) {
                asio::write(socket, asio::buffer(file_buffer.data(), static_cast<std::size_t>(count)));
            }
        }
        return true;
    } catch (const std::exception& ex) {
        error = ex.what();
        return false;
    }
}

void Node::accept_loop() {
    asio::io_context io;
    asio::ip::tcp::acceptor acceptor(io);
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(bind_host_), port_);
    std::error_code ec;
    acceptor.open(endpoint.protocol(), ec);
    if (ec) {
        last_error_ = ec.message();
        running_ = false;
        return;
    }
    acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true), ec);
    if (ec) {
        last_error_ = ec.message();
        running_ = false;
        return;
    }
    acceptor.bind(endpoint, ec);
    if (ec) {
        last_error_ = ec.message();
        running_ = false;
        return;
    }
    acceptor.listen(asio::socket_base::max_listen_connections, ec);
    if (ec) {
        last_error_ = ec.message();
        running_ = false;
        return;
    }
    port_ = acceptor.local_endpoint().port();

    while (running_) {
        asio::ip::tcp::socket socket(io);
        acceptor.accept(socket, ec);
        if (ec) {
            continue;
        }
        handle_connection(socket);
    }
}

bool Node::handle_connection(asio::ip::tcp::socket& socket) {
    Header header{};
    std::size_t total = 0;
    std::vector<std::uint8_t> header_buf(sizeof(Header));
    while (total < header_buf.size()) {
        std::error_code ec;
        std::size_t n = socket.read_some(asio::buffer(header_buf.data() + total, header_buf.size() - total), ec);
        if (ec || n == 0) {
            return false;
        }
        total += n;
    }
    std::memcpy(&header, header_buf.data(), sizeof(Header));
    if (header.magic != Magic || header.version != Version) {
        return false;
    }

    std::vector<char> name_buf(header.name_len);
    std::vector<char> mime_buf(header.mime_len);
    std::vector<std::uint8_t> tx_buf(header.tx_len);
    if (header.name_len > 0) {
        asio::read(socket, asio::buffer(name_buf.data(), name_buf.size()));
    }
    if (header.mime_len > 0) {
        asio::read(socket, asio::buffer(mime_buf.data(), mime_buf.size()));
    }
    if (header.tx_len > 0) {
        asio::read(socket, asio::buffer(tx_buf.data(), tx_buf.size()));
    }

    core::FileMetadata meta;
    meta.name.assign(name_buf.begin(), name_buf.end());
    meta.mime.assign(mime_buf.begin(), mime_buf.end());
    meta.size = header.file_size;

    fs::create_directories(storage_dir_);
    auto target_path = fs::path(storage_dir_) / meta.name;
    std::ofstream out(target_path, std::ios::binary);
    if (!out) {
        return false;
    }

    crypto_hash_sha256_state state;
    crypto_hash_sha256_init(&state);

    constexpr std::size_t chunk = 64 * 1024;
    std::vector<char> file_buf(chunk);
    std::uint64_t remaining = header.file_size;
    while (remaining > 0) {
        auto to_read = static_cast<std::size_t>(std::min<std::uint64_t>(remaining, chunk));
        asio::read(socket, asio::buffer(file_buf.data(), to_read));
        out.write(file_buf.data(), static_cast<std::streamsize>(to_read));
        crypto_hash_sha256_update(&state,
                                  reinterpret_cast<const unsigned char*>(file_buf.data()),
                                  static_cast<unsigned long long>(to_read));
        remaining -= to_read;
    }

    bool ok = true;
    core::HashBytes computed{};
    crypto_hash_sha256_final(&state, computed.data());
    if (computed != header.hash) {
        ok = false;
    }
    out.flush();

    if (ok && on_file_received_) {
        ReceivedFile info;
        info.sender = header.sender;
        info.receiver = header.receiver;
        info.hash = header.hash;
        info.metadata = meta;
        info.saved_path = target_path.string();
        info.tx_payload = std::move(tx_buf);
        on_file_received_(info);
    }
    return ok;
}

} // namespace network
