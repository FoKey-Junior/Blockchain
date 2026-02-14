#ifndef BLOCKCHAIN_NETWORK_NODE_H
#define BLOCKCHAIN_NETWORK_NODE_H

#include "core/types.h"
#include <asio.hpp>
#include <functional>
#include <string>
#include <thread>
#include <atomic>

namespace network {

struct ReceivedFile {
    core::AddressBytes sender;
    core::AddressBytes receiver;
    core::HashBytes hash;
    core::FileMetadata metadata;
    std::string saved_path;
    std::vector<std::uint8_t> tx_payload;
};

class Node {
public:
    using FileCallback = std::function<void(const ReceivedFile&)>;

    Node(std::string bind_host, std::uint16_t port, std::string storage_dir);
    ~Node();

    bool start();
    void stop();

    bool send_file(const std::string& host, std::uint16_t port,
                   const core::AddressBytes& sender,
                   const core::AddressBytes& receiver,
                   const std::string& path,
                   const core::FileMetadata& metadata,
                   core::HashBytes file_hash,
                   const std::vector<std::uint8_t>& tx_payload,
                   std::string& error);

    void set_on_file_received(FileCallback cb);

    std::uint16_t port() const noexcept { return port_; }
    std::string last_error() const noexcept { return last_error_; }

private:
    void accept_loop();
    bool handle_connection(asio::ip::tcp::socket& socket);

    std::string bind_host_;
    std::atomic<std::uint16_t> port_;
    std::string storage_dir_;
    FileCallback on_file_received_;
    std::string last_error_;

    std::atomic<bool> running_{false};
    std::thread worker_;
};

} // namespace network

#endif
