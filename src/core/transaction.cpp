#include "core/transaction.h"

#include <cstring>
#include <stdexcept>

namespace core {

namespace {
std::vector<std::uint8_t> encode_u64(std::uint64_t value) {
    std::vector<std::uint8_t> out(8);
    for (int i = 7; i >= 0; --i) {
        out[7 - i] = static_cast<std::uint8_t>((value >> (i * 8)) & 0xFF);
    }
    return out;
}

std::uint64_t decode_u64(const std::uint8_t* data) {
    std::uint64_t value = 0;
    for (int i = 0; i < 8; ++i) {
        value = (value << 8) | data[i];
    }
    return value;
}

void append_bytes(std::vector<std::uint8_t>& out, const std::uint8_t* data, std::size_t size) {
    out.insert(out.end(), data, data + size);
}

void append_string(std::vector<std::uint8_t>& out, const std::string& value) {
    const auto size_bytes = encode_u64(static_cast<std::uint64_t>(value.size()));
    append_bytes(out, size_bytes.data(), size_bytes.size());
    append_bytes(out, reinterpret_cast<const std::uint8_t*>(value.data()), value.size());
}
} // namespace

Transaction::Transaction(AddressBytes sender, AddressBytes receiver, HashBytes file_hash,
                         FileMetadata metadata, std::chrono::system_clock::time_point created_at)
    : sender_(sender),
      receiver_(receiver),
      file_hash_(file_hash),
      metadata_(std::move(metadata)),
      created_at_(created_at) {
    compute_id();
}

void Transaction::compute_id() noexcept {
    std::vector<std::uint8_t> data;
    append_bytes(data, sender_.data(), sender_.size());
    append_bytes(data, receiver_.data(), receiver_.size());
    append_bytes(data, file_hash_.data(), file_hash_.size());
    append_string(data, metadata_.name);
    append_string(data, metadata_.mime);
    const auto size_bytes = encode_u64(metadata_.size);
    append_bytes(data, size_bytes.data(), size_bytes.size());
    const auto timestamp = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(created_at_.time_since_epoch()).count());
    const auto time_bytes = encode_u64(timestamp);
    append_bytes(data, time_bytes.data(), time_bytes.size());

    id_ = crypto::blake2b_256(data);
}

namespace {
std::vector<std::uint8_t> signable_payload(const Transaction& tx) {
    std::vector<std::uint8_t> out;
    append_bytes(out, tx.id().data(), tx.id().size());
    append_bytes(out, tx.sender().data(), tx.sender().size());
    append_bytes(out, tx.receiver().data(), tx.receiver().size());
    append_bytes(out, tx.file_hash().data(), tx.file_hash().size());
    append_string(out, tx.metadata().name);
    append_string(out, tx.metadata().mime);
    const auto size_bytes = encode_u64(tx.metadata().size);
    append_bytes(out, size_bytes.data(), size_bytes.size());
    const auto timestamp = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(tx.created_at().time_since_epoch()).count());
    const auto time_bytes = encode_u64(timestamp);
    append_bytes(out, time_bytes.data(), time_bytes.size());
    return out;
}
} // namespace

void Transaction::sign(const PrivateKeyBytes& private_key) noexcept {
    auto data = signable_payload(*this);
    signature_ = crypto::sign(data, private_key);
}

bool Transaction::verify(const PublicKeyBytes& public_key) const noexcept {
    auto data = signable_payload(*this);
    return crypto::verify(data, signature_, public_key);
}

std::vector<std::uint8_t> Transaction::serialize() const {
    std::vector<std::uint8_t> out;
    append_bytes(out, id_.data(), id_.size());
    append_bytes(out, sender_.data(), sender_.size());
    append_bytes(out, receiver_.data(), receiver_.size());
    append_bytes(out, file_hash_.data(), file_hash_.size());
    append_string(out, metadata_.name);
    append_string(out, metadata_.mime);
    const auto size_bytes = encode_u64(metadata_.size);
    append_bytes(out, size_bytes.data(), size_bytes.size());
    const auto timestamp = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(created_at_.time_since_epoch()).count());
    const auto time_bytes = encode_u64(timestamp);
    append_bytes(out, time_bytes.data(), time_bytes.size());
    append_bytes(out, signature_.data(), signature_.size());
    return out;
}

Transaction Transaction::deserialize(const std::vector<std::uint8_t>& data) {
    std::size_t offset = 0;
    auto require = [&](std::size_t n) {
        if (offset + n > data.size()) {
            throw std::runtime_error("Transaction deserialize: out of range");
        }
    };

    Transaction tx({}, {}, {}, {}, std::chrono::system_clock::now());
    require(AddressSize);
    std::memcpy(tx.id_.data(), data.data() + offset, AddressSize);
    offset += AddressSize;

    require(AddressSize);
    std::memcpy(tx.sender_.data(), data.data() + offset, AddressSize);
    offset += AddressSize;

    require(AddressSize);
    std::memcpy(tx.receiver_.data(), data.data() + offset, AddressSize);
    offset += AddressSize;

    require(HashSize);
    std::memcpy(tx.file_hash_.data(), data.data() + offset, HashSize);
    offset += HashSize;

    require(8);
    auto name_len = decode_u64(data.data() + offset);
    offset += 8;
    require(static_cast<std::size_t>(name_len));
    tx.metadata_.name.assign(reinterpret_cast<const char*>(data.data() + offset),
                             static_cast<std::size_t>(name_len));
    offset += static_cast<std::size_t>(name_len);

    require(8);
    auto mime_len = decode_u64(data.data() + offset);
    offset += 8;
    require(static_cast<std::size_t>(mime_len));
    tx.metadata_.mime.assign(reinterpret_cast<const char*>(data.data() + offset),
                             static_cast<std::size_t>(mime_len));
    offset += static_cast<std::size_t>(mime_len);

    require(8);
    tx.metadata_.size = decode_u64(data.data() + offset);
    offset += 8;

    require(8);
    auto timestamp = decode_u64(data.data() + offset);
    offset += 8;
    tx.created_at_ = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));

    require(SignatureSize);
    std::memcpy(tx.signature_.data(), data.data() + offset, SignatureSize);
    offset += SignatureSize;

    return tx;
}

} // namespace core
