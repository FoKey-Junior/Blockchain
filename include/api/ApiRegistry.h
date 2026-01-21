#ifndef BLOCKCHAIN_API_REGISTRY_H
#define BLOCKCHAIN_API_REGISTRY_H

#include <string>
#include <vector>
#include <cstdint>

// Заголовок для регистрации майнеров без зависимости от Crow
// Это позволяет избежать конфликтов макросов Qt и Crow
namespace ApiRegistry {
    void register_miner(const std::string& ip, uint16_t port);
    std::vector<std::pair<std::string, uint16_t>> get_miners();
}

#endif
