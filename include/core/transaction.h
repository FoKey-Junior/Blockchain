#ifndef BLOCKCHAIN_CORE_TRANSACTION_H
#define BLOCKCHAIN_CORE_TRANSACTION_H

#include "types.h"
#include "crypto.h"
#include <chrono>
#include <vector>

namespace core {

class Transaction {
public:
    Transaction(AddressBytes sender, AddressBytes receiver, HashBytes file_hash,
                FileMetadata metadata, std::chrono::system_clock::time_point created_at);

    void sign(const PrivateKeyBytes& private_key) noexcept;
    bool verify(const PublicKeyBytes& public_key) const noexcept;

    AddressBytes id() const noexcept { return id_; }
    AddressBytes sender() const noexcept { return sender_; }
    AddressBytes receiver() const noexcept { return receiver_; }
    HashBytes file_hash() const noexcept { return file_hash_; }
    const FileMetadata& metadata() const noexcept { return metadata_; }
    std::chrono::system_clock::time_point created_at() const noexcept { return created_at_; }
    SignatureBytes signature() const noexcept { return signature_; }

    std::vector<std::uint8_t> serialize() const;
    static Transaction deserialize(const std::vector<std::uint8_t>& data);

private:
    AddressBytes id_{};
    AddressBytes sender_{};
    AddressBytes receiver_{};
    HashBytes file_hash_{};
    FileMetadata metadata_{};
    std::chrono::system_clock::time_point created_at_{};
    SignatureBytes signature_{};

    void compute_id() noexcept;
};

} // namespace core

#endif
