#include "core/block.h"

#include <cstring>
#include <stdexcept>

namespace core {

namespace {
void append_bytes(std::vector<std::uint8_t>& out, const std::uint8_t* data, std::size_t size) {
    out.insert(out.end(), data, data + size);
}

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

std::vector<std::uint8_t> signable_payload(const Block& block) {
    std::vector<std::uint8_t> out;
    out.reserve(256);

    append_bytes(out, block.previous_hash().data(), block.previous_hash().size());
    for (const auto& tx : block.transactions()) {
        const auto tx_data = tx.serialize();
        append_bytes(out, tx_data.data(), tx_data.size());
    }
    const auto timestamp = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(block.created_at().time_since_epoch()).count());
    const auto time_bytes = encode_u64(timestamp);
    append_bytes(out, time_bytes.data(), time_bytes.size());
    const auto nonce_bytes = encode_u64(block.nonce());
    append_bytes(out, nonce_bytes.data(), nonce_bytes.size());
    append_bytes(out, block.authority().data(), block.authority().size());
    return out;
}
} // namespace

Block::Block(HashBytes previous_hash, std::vector<Transaction> transactions,
             std::chrono::system_clock::time_point created_at,
             PublicKeyBytes authority, SignatureBytes authority_signature,
             std::uint64_t nonce)
    : previous_hash_(previous_hash),
      transactions_(std::move(transactions)),
      created_at_(created_at),
      authority_(authority),
      authority_signature_(authority_signature),
      nonce_(nonce) {
    compute_hash();
}

void Block::compute_hash() noexcept {
    std::vector<std::uint8_t> data;
    data.reserve(256);

    append_bytes(data, previous_hash_.data(), previous_hash_.size());
    for (const auto& tx : transactions_) {
        const auto tx_data = tx.serialize();
        append_bytes(data, tx_data.data(), tx_data.size());
    }
    const auto timestamp = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(created_at_.time_since_epoch()).count());
    const auto time_bytes = encode_u64(timestamp);
    append_bytes(data, time_bytes.data(), time_bytes.size());
    const auto nonce_bytes = encode_u64(nonce_);
    append_bytes(data, nonce_bytes.data(), nonce_bytes.size());
    append_bytes(data, authority_.data(), authority_.size());
    hash_ = crypto::blake2b_256(data);
}

bool Block::verify_authority() const noexcept {
    auto data = signable_payload(*this);
    return crypto::verify(data, authority_signature_, authority_);
}

std::vector<std::uint8_t> Block::serialize() const {
    std::vector<std::uint8_t> out;
    out.reserve(256);

    append_bytes(out, hash_.data(), hash_.size());
    append_bytes(out, previous_hash_.data(), previous_hash_.size());
    const auto count_bytes = encode_u64(static_cast<std::uint64_t>(transactions_.size()));
    append_bytes(out, count_bytes.data(), count_bytes.size());
    for (const auto& tx : transactions_) {
        const auto tx_data = tx.serialize();
        const auto tx_size_bytes = encode_u64(static_cast<std::uint64_t>(tx_data.size()));
        append_bytes(out, tx_size_bytes.data(), tx_size_bytes.size());
        append_bytes(out, tx_data.data(), tx_data.size());
    }
    const auto timestamp = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(created_at_.time_since_epoch()).count());
    const auto time_bytes = encode_u64(timestamp);
    append_bytes(out, time_bytes.data(), time_bytes.size());
    const auto nonce_bytes = encode_u64(nonce_);
    append_bytes(out, nonce_bytes.data(), nonce_bytes.size());
    append_bytes(out, authority_.data(), authority_.size());
    append_bytes(out, authority_signature_.data(), authority_signature_.size());
    return out;
}

Block Block::deserialize(const std::vector<std::uint8_t>& data) {
    std::size_t offset = 0;
    auto require = [&](std::size_t n) {
        if (offset + n > data.size()) {
            throw std::runtime_error("Block deserialize: out of range");
        }
    };

    Block block({}, {}, std::chrono::system_clock::now(), {}, {}, 0);
    require(HashSize);
    std::memcpy(block.hash_.data(), data.data() + offset, HashSize);
    offset += HashSize;

    require(HashSize);
    std::memcpy(block.previous_hash_.data(), data.data() + offset, HashSize);
    offset += HashSize;

    require(8);
    auto count = decode_u64(data.data() + offset);
    offset += 8;
    block.transactions_.clear();
    block.transactions_.reserve(static_cast<std::size_t>(count));
    for (std::size_t i = 0; i < count; ++i) {
        require(8);
        auto tx_size = decode_u64(data.data() + offset);
        offset += 8;
        require(static_cast<std::size_t>(tx_size));
        std::vector<std::uint8_t> tx_data(data.begin() + static_cast<std::ptrdiff_t>(offset),
                                          data.begin() + static_cast<std::ptrdiff_t>(offset + tx_size));
        offset += static_cast<std::size_t>(tx_size);
        block.transactions_.push_back(Transaction::deserialize(tx_data));
    }

    require(8);
    auto timestamp = decode_u64(data.data() + offset);
    offset += 8;
    block.created_at_ = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));

    require(8);
    block.nonce_ = decode_u64(data.data() + offset);
    offset += 8;

    require(PublicKeySize);
    std::memcpy(block.authority_.data(), data.data() + offset, PublicKeySize);
    offset += PublicKeySize;

    require(SignatureSize);
    std::memcpy(block.authority_signature_.data(), data.data() + offset, SignatureSize);
    offset += SignatureSize;

    return block;
}

} // namespace core
