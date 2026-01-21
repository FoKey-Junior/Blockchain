#include "../../include/network/Node.h"
#include "../../include/blockchain/Transaction.h"
#include "../../include/blockchain/Blockchain.h"
#include <iostream>
#include <cstring>

Node::Node(asio::io_context& io, uint16_t port,
           const unsigned char* pub_key, const unsigned char* priv_key) noexcept
    : io_context_(io),
      acceptor_(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    std::memcpy(pub_key_, pub_key, crypto_sign_PUBLICKEYBYTES);
    std::memcpy(priv_key_, priv_key, crypto_sign_SECRETKEYBYTES);
}

void Node::start() noexcept {
    accept();
}

// Асинхронный accept
void Node::accept() noexcept {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](auto ec) {
        if (!ec) {
            std::cout << "[Node] New client connected from " 
                      << socket->remote_endpoint().address().to_string() << ":"
                      << socket->remote_endpoint().port() << "\n";
            
            // Добавляем нового клиента в список пиров
            Peer peer(socket->remote_endpoint().address().to_string(), 
                     socket->remote_endpoint().port(), pub_key_);
            std::lock_guard<std::mutex> lock(peers_mutex_);
            peers_.push_back(PeerConnection{peer, socket});
            std::cout << "[Node] Client added to peers list, total peers: " << peers_.size() << "\n";
            
            handle_connection(socket);
        }
        accept();
    });
}

// Обработка соединения
void Node::handle_connection(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept {
    std::cout << "[Node] Handling new connection, starting to read messages\n";
    read_message(socket);
}

// Чтение сообщений
void Node::read_message(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept {
    auto buf = std::make_shared<std::vector<uint8_t>>(8192); // Увеличиваем буфер для блоков
    socket->async_read_some(asio::buffer(*buf), [this, buf, socket](auto ec, std::size_t length) {
        if (!ec && length > 0) {
            std::cout << "[Node] Received " << length << " bytes from peer\n";
            buf->resize(length);
            Message msg = deserialize_message(*buf);

            std::vector<uint8_t> unsigned_payload;
            if (CryptoUtils::verify_message(msg.payload, msg.sender_pub_key.data(), unsigned_payload)) {
                if (!unsigned_payload.empty()) {
                    std::cout << "[Node] Message verified, handling message type: " << static_cast<int>(msg.type) << "\n";
                    handle_message(msg.type, unsigned_payload);
                } else {
                    std::cout << "[Node] Warning: Empty payload after verification\n";
                }
            } else {
                std::cout << "[Node] Warning: Message verification failed\n";
            }

            read_message(socket);
        } else if (ec) {
            std::cout << "[Node] Error reading from peer: " << ec.message() << "\n";
            std::lock_guard<std::mutex> lock(peers_mutex_);
            peers_.erase(std::remove_if(peers_.begin(), peers_.end(),
                                        [socket](const PeerConnection& pc){ return pc.socket == socket; }),
                         peers_.end());
        }
    });
}

// Подключение к пиру
void Node::connect_to_peer(const std::string& ip, uint16_t port) noexcept {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);
    asio::ip::tcp::endpoint ep(asio::ip::make_address(ip), port);
    socket->async_connect(ep, [this, socket, ip, port](auto ec){
        if (!ec) {
            Peer peer(ip, port, pub_key_);
            std::lock_guard<std::mutex> lock(peers_mutex_);
            peers_.push_back(PeerConnection{peer, socket});
            handle_connection(socket);
        }
    });
}

// Рассылка
void Node::broadcast_message(const Message& msg) noexcept {
    std::vector<uint8_t> full_msg = serialize_message(msg);
    std::lock_guard<std::mutex> lock(peers_mutex_);

    if (peers_.empty()) {
        std::cout << "[Node] Warning: No peers to broadcast message to!\n";
        return;
    }

    std::cout << "[Node] Broadcasting message to " << peers_.size() << " peer(s)\n";

    for (auto it = peers_.begin(); it != peers_.end();) {
        auto& pc = *it;
        auto socket = pc.socket;
        asio::async_write(*socket, asio::buffer(full_msg),
                          [this, socket, &it](auto ec, std::size_t written){
                              if (ec) {
                                  std::cout << "[Node] Error sending message to peer: " << ec.message() << "\n";
                                  std::lock_guard<std::mutex> lock(peers_mutex_);
                                  it = peers_.erase(it);
                              } else {
                                  std::cout << "[Node] Message sent successfully (" << written << " bytes)\n";
                              }
                          });
        ++it;
    }
}

// Добавление транзакции
void Node::add_transaction(const std::vector<uint8_t>& tx) noexcept {
    std::cout << "[Node] Adding transaction to local mempool, size: " << tx.size() << " bytes\n";
    std::lock_guard<std::mutex> lock(mempool_mutex_);
    mempool_.push_back(tx);
    std::cout << "[Node] Transaction added, processing mempool...\n";
    process_mempool();
}

// Обработка мемпула - рассылка транзакций другим пирам
void Node::process_mempool() noexcept {
    while (!mempool_.empty()) {
        auto tx = mempool_.front();
        mempool_.erase(mempool_.begin());

        Message msg;
        msg.type = MessageType::NEW_TX;
        std::memcpy(msg.sender_pub_key.data(), pub_key_, crypto_sign_PUBLICKEYBYTES);
        msg.payload = CryptoUtils::sign_message(tx, priv_key_);

        std::cout << "[Node] Broadcasting NEW_TX message to peers...\n";
        broadcast_message(msg);
        std::cout << "[Node] Transaction broadcasted\n";
    }
}

// Обработка входящих сообщений
void Node::handle_message(MessageType type, const std::vector<uint8_t>& payload) noexcept {
    switch (type) {
        case MessageType::NEW_TX: {
            // Десериализуем транзакцию и добавляем в mempool майнера
            auto tx_opt = Transaction::deserialize(payload);
            if (tx_opt.has_value() && mempool) {
                std::lock_guard<std::mutex> lock(mempool_mutex_);
                // Проверяем, нет ли уже такой транзакции
                bool exists = false;
                for (const auto& existing_tx : *mempool) {
                    if (std::memcmp(existing_tx.get_address_bytes(), 
                                   tx_opt->get_address_bytes(),
                                   crypto_generichash_BYTES) == 0) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    mempool->push_back(tx_opt.value());
                    std::cout << "[Node] ✓ New transaction received and added to mempool\n";
                    std::cout << "[Node] Transaction will be processed by miner shortly...\n";
                } else {
                    std::cout << "[Node] Transaction already exists in mempool, skipping\n";
                }
            }
            break;
        }
        case MessageType::NEW_BLOCK: {
            // Обрабатываем новый блок от другого майнера
            std::cout << "[Node] Received NEW_BLOCK message from peer, payload size: " << payload.size() << "\n";
            
            // В текущей реализации отправляется только адрес блока
            // Для полной синхронизации нужно будет отправлять полный блок
            // Пока добавляем простой блок с полученным адресом
            if (payload.size() >= crypto_generichash_BYTES && blockchain) {
                unsigned char block_address[crypto_generichash_BYTES];
                std::memcpy(block_address, payload.data(), crypto_generichash_BYTES);
                
                // Получаем адрес предыдущего блока
                const unsigned char* prev_addr = blockchain->last_block().get_address();
                unsigned char sender_addr[crypto_generichash_BYTES] = {};
                unsigned char receiver_addr[crypto_generichash_BYTES] = {};
                std::memcpy(sender_addr, prev_addr, crypto_generichash_BYTES);
                std::memcpy(receiver_addr, prev_addr, crypto_generichash_BYTES);
                
                // Создаем новый блок
                auto now = std::chrono::system_clock::now();
                std::unordered_map<std::string, FileMetadata> empty_files;
                Block new_block(block_address, prev_addr, sender_addr, receiver_addr, now, empty_files);
                
                // Добавляем блок в блокчейн
                blockchain->add_block_direct(new_block);
                std::cout << "[Node] ✓ New block added to blockchain! Total blocks: " << blockchain->size() << "\n";
                
                // Вызываем callback для обновления UI
                if (on_blockchain_updated) {
                    std::cout << "[Node] Calling blockchain update callback...\n";
                    on_blockchain_updated();
                } else {
                    std::cout << "[Node] Warning: No blockchain update callback set!\n";
                }
            } else {
                if (!blockchain) {
                    std::cout << "[Node] Warning: Blockchain not set in Node\n";
                } else {
                    std::cout << "[Node] Warning: Invalid block payload size: " << payload.size() << " (expected at least " << crypto_generichash_BYTES << ")\n";
                }
            }
            break;
        }
        case MessageType::TX_PROCESSED: {
            // Уведомление от майнера о том, что транзакция обработана
            std::cout << "[Node] ✓ Transaction processed successfully by miner!\n";
            std::cout << "[Node] Your transaction has been included in a block\n";
            break;
        }
        case MessageType::HELLO:
        case MessageType::PING:
        case MessageType::PONG:
        case MessageType::PEER_LIST:
            // Обработка других типов сообщений
            break;
    }
}

// Сериализация
std::vector<uint8_t> Node::serialize_message(const Message& msg) const noexcept {
    std::vector<uint8_t> buf;
    buf.push_back(static_cast<uint8_t>(msg.type));
    buf.insert(buf.end(), msg.sender_pub_key.begin(), msg.sender_pub_key.end());
    buf.insert(buf.end(), msg.payload.begin(), msg.payload.end());
    return buf;
}

// Десериализация
Message Node::deserialize_message(const std::vector<uint8_t>& buf) const noexcept {
    Message msg;
    if (buf.size() >= 1 + crypto_sign_PUBLICKEYBYTES) {
        msg.type = static_cast<MessageType>(buf[0]);
        std::memcpy(msg.sender_pub_key.data(), buf.data() + 1, crypto_sign_PUBLICKEYBYTES);
        msg.payload.assign(buf.begin() + 1 + crypto_sign_PUBLICKEYBYTES, buf.end());
    }
    return msg;
}


void Node::connect_to_server(const std::string& host, uint16_t port) noexcept {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);
    asio::ip::tcp::resolver resolver(io_context_);
    auto endpoints = resolver.resolve(host, std::to_string(port));

    asio::async_connect(*socket, endpoints,
        [this, socket, host, port](const std::error_code& ec, const asio::ip::tcp::endpoint&) {
            if (!ec) {
                // Добавляем сервер в список пиров, чтобы можно было отправлять ему сообщения
                Peer peer(host, port, pub_key_);
                std::lock_guard<std::mutex> lock(peers_mutex_);
                peers_.push_back(PeerConnection{peer, socket});
                std::cout << "[Node] Connected to server " << host << ":" << port << "\n";
                std::cout << "[Node] Server added to peers list, total peers: " << peers_.size() << "\n";
                handle_connection(socket); // <- вызываем приватный метод внутри Node
            } else {
                std::cerr << "[Node] Failed to connect to server: " << ec.message() << "\n";
            }
        }
    );
}

// Рассылка блока другим майнерам
void Node::broadcast_block(const Block& block) noexcept {
    // Для простоты сериализуем только адрес блока
    // В полной реализации нужно сериализовать весь блок
    std::vector<uint8_t> block_data;
    const unsigned char* addr = block.get_address();
    block_data.insert(block_data.end(), addr, addr + crypto_generichash_BYTES);
    
    Message msg;
    msg.type = MessageType::NEW_BLOCK;
    std::memcpy(msg.sender_pub_key.data(), pub_key_, crypto_sign_PUBLICKEYBYTES);
    msg.payload = CryptoUtils::sign_message(block_data, priv_key_);
    
    broadcast_message(msg);
    std::cout << "[Node] Broadcasted new block\n";
}
// Уведомление клиентов о завершении обработки транзакций
void Node::notify_tx_processed(const std::vector<Transaction>& txs) noexcept {
    if (txs.empty()) {
        return;
    }
    
    // Создаем уведомление о каждой обработанной транзакции
    for (const auto& tx : txs) {
        // Сериализуем адрес транзакции для уведомления
        std::vector<uint8_t> tx_data;
        const unsigned char* tx_addr = tx.get_address_bytes();
        tx_data.insert(tx_data.end(), tx_addr, tx_addr + crypto_generichash_BYTES);
        
        Message msg;
        msg.type = MessageType::TX_PROCESSED;
        std::memcpy(msg.sender_pub_key.data(), pub_key_, crypto_sign_PUBLICKEYBYTES);
        msg.payload = CryptoUtils::sign_message(tx_data, priv_key_);
        
        // Отправляем уведомление всем подключенным пирам (клиентам и майнерам)
        std::lock_guard<std::mutex> lock(peers_mutex_);
        if (!peers_.empty()) {
            std::cout << "[Node] Notifying " << peers_.size() << " peer(s) about processed transaction\n";
            broadcast_message(msg);
        } else {
            std::cout << "[Node] No peers connected to notify\n";
        }
    }
}
