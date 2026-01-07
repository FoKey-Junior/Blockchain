#include "../../include/core/Block.h"

Block::Block(
    const unsigned char* address_data,
    const unsigned char* previous_address_data,
    const unsigned char* sender_data,
    const unsigned char* receiver_data,
    std::chrono::system_clock::time_point time_creation,
    uint64_t amount
) : time_creation(time_creation), amount(amount) {

    std::memcpy(this->address, address_data, crypto_generichash_BYTES);
    std::memcpy(this->previous_address, previous_address_data, crypto_generichash_BYTES);
    std::memcpy(this->sender, sender_data, crypto_generichash_BYTES);
    std::memcpy(this->receiver, receiver_data, crypto_generichash_BYTES);

    print();
}


static void print_hex(const unsigned char* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(data[i]);
    }
    std::cout << std::dec;
}

void Block::print() const {
    std::cout << "\n==================== BLOCK ====================\n";

    std::cout << "Address:          ";
    print_hex(address, crypto_generichash_BYTES);
    std::cout << "\n";

    std::cout << "Previous address: ";
    print_hex(previous_address, crypto_generichash_BYTES);
    std::cout << "\n";

    std::cout << "Sender:           ";
    print_hex(sender, crypto_generichash_BYTES);
    std::cout << "\n";

    std::cout << "Receiver:         ";
    print_hex(receiver, crypto_generichash_BYTES);
    std::cout << "\n";

    std::time_t t = std::chrono::system_clock::to_time_t(time_creation);
    std::cout << "Time:             "
              << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S")
              << "\n";

    std::cout << "Amount:           " << amount << "\n";

    std::cout << "===============================================\n";
}