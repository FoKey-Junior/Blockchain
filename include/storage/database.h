#ifndef BLOCKCHAIN_STORAGE_DATABASE_H
#define BLOCKCHAIN_STORAGE_DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>

namespace storage {

class Database {
public:
    explicit Database(std::string path);
    ~Database();

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    void init_schema();
    void execute(const std::string& sql);

    sqlite3* handle() const noexcept { return db_; }
    const std::string& path() const noexcept { return path_; }

private:
    sqlite3* db_{nullptr};
    std::string path_;
};

} // namespace storage

#endif
