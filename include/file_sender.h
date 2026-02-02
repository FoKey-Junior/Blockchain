#ifndef FILE_SENDER_H
#define FILE_SENDER_H

#include "types.h"
#include "user.h"
#include "transaction.h"
#include <vector>
#include <string>
#include <unordered_map>

class node;

class file_sender {
private:
    address_bytes sender_address_;
    address_bytes receiver_address_;
    std::vector<std::string> file_names_;
    std::vector<std::string> file_paths_;
    const user& user_ref_;
    node& node_ref_;

    [[nodiscard]] std::unordered_map<std::string, file_metadata> prepare_files() const noexcept(false);

public:
    file_sender(
        const address_bytes& sender_address,
        const address_bytes& receiver_address,
        std::vector<std::string> file_names,
        std::vector<std::string> file_paths,
        const user& user_ref,
        node& node_ref
    ) noexcept;

    ~file_sender() = default;

    file_sender(const file_sender&) = delete;
    file_sender& operator=(const file_sender&) = delete;
    file_sender(file_sender&&) noexcept = default;
    file_sender& operator=(file_sender&&) noexcept = default;

    void prepare_and_send() noexcept(false);
};

#endif

