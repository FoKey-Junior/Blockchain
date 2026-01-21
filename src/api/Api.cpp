#include "../../include/api/Api.h"
#include "../../include/api/ApiRegistry.h"
#include "../../include/blockchain/User.h"
#include "../../include/blockchain/Transaction.h"
#include "../../include/blockchain/Mempool.h"
#include "../../include/blockchain/Miner.h"
#include "../../include/network/Node.h"
#include "../../include/network/CryptoUtils.h"
#include <asio.hpp>
#include <sodium.h>
#include <cstring>
#include <iostream>

std::vector<std::pair<std::string, uint16_t>> Api::miner_addresses;
std::mutex Api::miner_addresses_mutex;

// Реализация для ApiRegistry (использует те же статические переменные)
namespace ApiRegistry {
    void register_miner(const std::string& ip, uint16_t port) {
        Api::register_miner(ip, port);
    }
    
    std::vector<std::pair<std::string, uint16_t>> get_miners() {
        return Api::get_miners();
    }
}

void Api::register_miner(const std::string& ip, uint16_t port) {
    std::lock_guard<std::mutex> lock(miner_addresses_mutex);
    // Проверяем, нет ли уже этого майнера
    for (const auto& [existing_ip, existing_port] : miner_addresses) {
        if (existing_ip == ip && existing_port == port) {
            return;
        }
    }
    miner_addresses.push_back({ip, port});
    std::cout << "[API] Registered miner: " << ip << ":" << port << "\n";
}

std::vector<std::pair<std::string, uint16_t>> Api::get_miners() {
    std::lock_guard<std::mutex> lock(miner_addresses_mutex);
    return miner_addresses;
}

void Api::start_server(unsigned short const port) {
    if (sodium_init() < 0) {
        std::cerr << "libsodium init failed in API\n";
        return;
    }

    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Warning);

    // Создаем Node для отправки транзакций майнерам
    User api_user;
    asio::io_context io_context;
    Node api_node(io_context, 0, api_user.get_public_key(), api_user.get_private_key());
    
    // Запускаем io_context в отдельном потоке
    std::thread io_thread([&io_context]() {
        io_context.run();
    });
    io_thread.detach();
    
    // Запускаем Node
    api_node.start();

    CROW_ROUTE(app, "/favicon.ico")([]() {
        return crow::response(200, "");
    });

    // Регистрация майнера
    CROW_ROUTE(app, "/api/register/miner").methods("POST"_method)
    ([](const crow::request& req) {
        try {
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invalid JSON");
            }

            std::string ip = body["ip"].s();
            uint16_t port = body["port"].i();
            
            Api::register_miner(ip, port);
            return crow::response(200, "Miner registered");
        } catch (...) {
            return crow::response(400, "Invalid request");
        }
    });

    // Получение списка майнеров
    CROW_ROUTE(app, "/api/get/list_miners")([]() {
        auto miners = Api::get_miners();
        crow::json::wvalue result;
        result["count"] = miners.size();
        crow::json::wvalue::list miners_list;
        for (const auto& [ip, port] : miners) {
            crow::json::wvalue miner;
            miner["ip"] = ip;
            miner["port"] = port;
            miners_list.push_back(miner);
        }
        result["miners"] = std::move(miners_list);
        return crow::response(result);
    });

    // Отправка транзакции майнерам
    CROW_ROUTE(app, "/api/send/transaction").methods("POST"_method)
    ([&api_node](const crow::request& req) {
        try {
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "Invalid JSON");
            }

            // Получаем данные транзакции из JSON
            std::string sender_hex = body["sender"].s();
            std::string receiver_hex = body["receiver"].s();
            
            // Конвертируем hex строку в байты
            auto hex_to_bytes = [](const std::string& hex) -> std::vector<unsigned char> {
                std::vector<unsigned char> bytes;
                for (size_t i = 0; i < hex.length(); i += 2) {
                    std::string byte_str = hex.substr(i, 2);
                    bytes.push_back(static_cast<unsigned char>(std::stoul(byte_str, nullptr, 16)));
                }
                return bytes;
            };
            
            std::vector<unsigned char> sender_bytes = hex_to_bytes(sender_hex);
            std::vector<unsigned char> receiver_bytes = hex_to_bytes(receiver_hex);
            
            if (sender_bytes.size() != crypto_generichash_BYTES || receiver_bytes.size() != crypto_generichash_BYTES) {
                return crow::response(400, "Invalid address format");
            }

            // Создаем транзакцию
            std::unordered_map<std::string, FileMetadata> files;
            Transaction tx(
                sender_bytes.data(),
                receiver_bytes.data(),
                files
            );

            // Сериализуем транзакцию
            std::vector<uint8_t> tx_data = tx.serialize();

            // Отправляем транзакцию всем зарегистрированным майнерам
            auto miners = Api::get_miners();
            for (const auto& [ip, port] : miners) {
                api_node.connect_to_peer(ip, port);
                // Небольшая задержка для установки соединения
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                api_node.add_transaction(tx_data);
            }

            return crow::response(200, "Transaction sent to miners");
        } catch (const std::exception& e) {
            return crow::response(400, std::string("Error: ") + e.what());
        } catch (...) {
            return crow::response(400, "Unknown error");
        }
    });

    //
    // CROW_ROUTE(app, "/api/new/miner")([&mempool, &alice, &bob](){
    //     Transaction transaction(alice.get_address_bytes(), bob.get_address_bytes());
    //     transaction.sign(alice.get_private_key());
    //
    //     if (transaction.verify(alice.get_public_key())) {
    //         mempool.add_transaction(transaction);
    //         std::cout << "Signature valid!\n";
    //     }
    //
    //     transaction.print();
    //
    //     return "miner started";
    // });
    //
    // CROW_ROUTE(app, "/api/mempool/pop")
    // ([&mempool](const crow::request& req) {
    //     auto txid = req.url_params.get("txid");
    //     if (!txid) {
    //         return crow::response(400, "txid required");
    //     }
    //
    //     bool removed = mempool.remove_transaction(
    //         reinterpret_cast<const unsigned char*>(txid)
    //     );
    //
    //     return removed
    //         ? crow::response(200, "transaction removed")
    //         : crow::response(404, "transaction not found");
    // });
    //
    // CROW_ROUTE(app, "/api/new/user")([](){
    //     User user;
    //     return "the new wallet has been successfully created";
    // });

    app.port(port).run();
}
