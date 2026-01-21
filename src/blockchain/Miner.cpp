#include "../../include/blockchain/Miner.h"
#include "../../include/network/Node.h"
#include <thread>
#include <iostream>
#include <chrono>

Miner::Miner(std::vector<Transaction>& mempool_) : mempool(mempool_) {}

void Miner::start_mining() {
    std::thread([this]() {
        int block_number = 0;
        std::cout << "[Miner] Starting mining process...\n";
        
        while (true) {
            std::vector<Transaction> txs;
            {
                if (mempool_mutex_ptr) {
                    std::lock_guard<std::mutex> lock(*mempool_mutex_ptr);
                    if (!mempool.empty()) {
                        std::cout << "[Miner] Found " << mempool.size() << " transaction(s) in mempool\n";
                        txs = mempool;
                        mempool.clear();
                        std::cout << "[Miner] Mempool cleared, starting block creation\n";
                    }
                } else {
                    // Если мьютекс не установлен, используем небезопасный доступ (для обратной совместимости)
                    if (!mempool.empty()) {
                        std::cout << "[Miner] Found " << mempool.size() << " transaction(s) in mempool (no mutex)\n";
                        txs = mempool;
                        mempool.clear();
                    }
                }
            }

            if (!txs.empty() && blockchain) {
                block_number++;
                auto start_time = std::chrono::steady_clock::now();
                
                std::cout << "[Miner] ========================================\n";
                std::cout << "[Miner] Block #" << block_number << " - Mining started\n";
                std::cout << "[Miner] Processing " << txs.size() << " transaction(s)...\n";
                
                // Выводим информацию о каждой транзакции
                for (size_t i = 0; i < txs.size(); ++i) {
                    const auto& tx = txs[i];
                    std::cout << "[Miner]   TX #" << (i + 1) << ": Processing transaction...\n";
                }
                
                blockchain->add_block(txs);
                const Block& new_block = blockchain->last_block();
                
                auto end_time = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                
                std::cout << "[Miner] Block #" << block_number << " successfully created!\n";
                std::cout << "[Miner] Block hash: ";
                // Выводим первые 8 байт адреса блока в hex
                const unsigned char* addr = new_block.get_address();
                for (int i = 0; i < 8; ++i) {
                    printf("%02x", addr[i]);
                }
                std::cout << "...\n";
                std::cout << "[Miner] Processing time: " << duration.count() << " ms\n";
                
                // Рассылаем блок другим майнерам через Node
                if (node_ptr) {
                    std::cout << "[Miner] Broadcasting block to other miners...\n";
                    node_ptr->broadcast_block(new_block);
                    
                    // Отправляем уведомления клиентам о завершении обработки транзакций
                    std::cout << "[Miner] Notifying clients about processed transactions...\n";
                    node_ptr->notify_tx_processed(txs);
                }
                
                std::cout << "[Miner] Block #" << block_number << " mining completed\n";
                std::cout << "[Miner] ========================================\n\n";
                
                std::this_thread::sleep_for(std::chrono::seconds(1)); // имитация PoW
            } else {
                // Периодически проверяем, но не спамим логи
                static int idle_count = 0;
                idle_count++;
                if (idle_count % 50 == 0) {  // Логируем каждые 50 проверок (~10 секунд)
                    std::cout << "[Miner] Waiting for transactions... (mempool empty)\n";
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }).detach();
}
