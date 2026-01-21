#ifndef BLOCKCHAIN_API_H
#define BLOCKCHAIN_API_H

#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include "crow.h"

class Node;

class Api {
private:
    static std::vector<std::pair<std::string, uint16_t>> miner_addresses;
    static std::mutex miner_addresses_mutex;

public:
    static void start_server(unsigned short const port);
    static void register_miner(const std::string& ip, uint16_t port);
    static std::vector<std::pair<std::string, uint16_t>> get_miners();
};

#endif