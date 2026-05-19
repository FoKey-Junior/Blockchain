#include "gui/app_controller.h"
#include "core/crypto.h"
#include "core/transaction.h"
#include "core/log.h"

#include <QDir>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QStandardPaths>
#include <QUrl>

namespace {
constexpr int kHexNibbleCount = 2;

bool isHexAddress(const QString& value, int bytes) {
    if (value.length() != bytes * kHexNibbleCount) {
        return false;
    }
    for (const QChar ch : value) {
        if (!ch.isDigit() && (ch.toLower() < 'a' || ch.toLower() > 'f')) {
            return false;
        }
    }
    return true;
}

void set_error(QString& out, const char* message) {
    out = QString::fromUtf8(message);
}
} // namespace

AppController::AppController(QObject* parent)
    : QObject(parent) {
    connect(&mempool_timer_, &QTimer::timeout, this, &AppController::process_mempool);
}

AppController::~AppController() {
    if (node_) {
        node_->stop();
    }
}

static QString normalizePath(const QString& input) {
    if (input.startsWith("file:")) {
        return QUrl(input).toLocalFile();
    }
    return input;
}

QString AppController::currentUserName() const {
    return current_user_ ? QString::fromStdString(current_user_->name()) : QString();
}

QString AppController::currentUserAddress() const {
    if (!current_user_) {
        return {};
    }
    return QString::fromStdString(core::crypto::to_hex(current_user_->address()));
}

bool AppController::initialize(const QString& dataDir, const QString& host, int port) {
    if (!core::crypto::init()) {
        core::log::write(core::log::Level::Error, "Failed to init libsodium");
        return false;
    }
    data_dir_ = dataDir;
    QDir().mkpath(data_dir_);
    const auto db_path = data_dir_ + "/blockchain.db";
    db_ = std::make_unique<storage::Database>(db_path.toStdString());
    db_->init_schema();
    user_store_ = std::make_unique<storage::UserStore>(*db_);
    tx_store_ = std::make_unique<storage::TxStore>(*db_);
    block_store_ = std::make_unique<storage::BlockStore>(*db_);

    const auto files_dir = data_dir_ + "/files";
    QDir().mkpath(files_dir);
    node_ = std::make_unique<network::Node>(host.toStdString(),
                                            static_cast<std::uint16_t>(port),
                                            files_dir.toStdString());
    node_->set_on_file_received([this](const network::ReceivedFile& file) { on_file_received(file); });
    node_->start();
    if (!node_->last_error().empty()) {
        core::log::write(core::log::Level::Error, "Node start failed: " + node_->last_error());
        emit notification(QString::fromStdString("Ошибка запуска узла: " + node_->last_error()));
    }
    core::log::write(core::log::Level::Info, "Node started on " + host.toStdString() + ":" + std::to_string(port));

    mempool_timer_.start(1500);
    load_models();
    return true;
}

bool AppController::initializeDefault(const QString& host, int port) {
    const auto dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return initialize(dir, host, port);
}

bool AppController::registerUser(const QString& name, const QString& host, int port, QString& error) {
    if (!user_store_) {
        set_error(error, "Storage not initialized");
        return false;
    }
    if (name.trimmed().isEmpty()) {
        set_error(error, "Name is required");
        return false;
    }
    try {
        const auto pair = core::crypto::generate_keypair();
        core::User user(name.toStdString(), pair);
        const auto address_hex = core::crypto::to_hex(user.address());

        storage::StoredUser stored;
        stored.name = user.name();
        stored.address_hex = address_hex;
        stored.public_key = user.public_key();
        stored.private_key = user.private_key();
        stored.host = host.toStdString();
        stored.port = static_cast<std::uint16_t>(port);
        user_store_->add_user(stored);
        core::log::write(core::log::Level::Info, "User registered: " + stored.name);

        current_user_ = std::make_unique<core::User>(user);
        blockchain_ = std::make_unique<core::Blockchain>(user.public_key());
        restart_node(host, port);
        emit currentUserChanged();
        load_models();
        return true;
    } catch (const std::exception& ex) {
        error = ex.what();
        return false;
    }
}

bool AppController::loginByAddress(const QString& address, QString& error) {
    if (!user_store_) {
        set_error(error, "Storage not initialized");
        return false;
    }
    if (!isHexAddress(address, static_cast<int>(core::AddressSize))) {
        set_error(error, "Invalid address");
        return false;
    }
    const auto list = user_store_->find_by_address(address.toStdString());
    if (list.empty()) {
        error = "User not found";
        return false;
    }
    const auto& stored = list.front();
    core::crypto::KeyPair keys{stored.public_key, stored.private_key};
    current_user_ = std::make_unique<core::User>(stored.name, keys);
    blockchain_ = std::make_unique<core::Blockchain>(stored.public_key);
    restart_node(QString::fromStdString(stored.host), stored.port);
    emit currentUserChanged();
    load_models();
    return true;
}

void AppController::refresh() {
    load_models();
}

bool AppController::sendFile(const QString& receiverAddress, const QString& filePath, QString& error) {
    if (!current_user_) {
        set_error(error, "Not logged in");
        return false;
    }
    if (!node_ || !user_store_) {
        set_error(error, "Network is not initialized");
        return false;
    }
    if (!isHexAddress(receiverAddress, static_cast<int>(core::AddressSize))) {
        set_error(error, "Invalid receiver address");
        return false;
    }
    const auto localPath = normalizePath(filePath);
    QFileInfo info(localPath);
    if (!info.exists() || !info.isFile()) {
        set_error(error, "File not found");
        return false;
    }

    const auto receiver_list = user_store_->find_by_address(receiverAddress.toStdString());
    if (receiver_list.empty()) {
        set_error(error, "Receiver not found");
        return false;
    }
    const auto& receiver = receiver_list.front();

    bool ok = false;
    const auto hash = core::crypto::sha256_file(localPath.toStdString(), ok);
    if (!ok) {
        set_error(error, "Failed to compute hash");
        return false;
    }

    QMimeDatabase mime_db;
    const auto mime = mime_db.mimeTypeForFile(filePath).name();

    core::FileMetadata meta;
    meta.name = info.fileName().toStdString();
    meta.size = static_cast<std::uint64_t>(info.size());
    meta.mime = mime.toStdString();

    const auto receiver_addr = core::crypto::address_from_hex(receiverAddress.toStdString());
    core::Transaction tx(current_user_->address(),
                         receiver_addr,
                         hash,
                         meta,
                         std::chrono::system_clock::now());
    tx.sign(current_user_->private_key());
    auto payload = tx.serialize();

    std::string send_error;
    const auto success = node_->send_file(receiver.host, receiver.port,
                                          current_user_->address(),
                                          receiver_addr,
                                          localPath.toStdString(),
                                          meta,
                                          hash,
                                          payload,
                                          send_error);
    if (!success) {
        error = QString::fromStdString(send_error);
        core::log::write(core::log::Level::Error, "Send failed: " + send_error);
        return false;
    }

    mempool_.push(tx);
    process_mempool();
    emit notification("Файл отправлен и записан в блокчейн");
    return true;
}

QVariantMap AppController::verifyFile(const QString& filePath) {
    QVariantMap result;
    const auto localPath = normalizePath(filePath);
    QFileInfo info(localPath);
    if (!info.exists()) {
        result["ok"] = false;
        result["error"] = "File not found";
        return result;
    }
    bool ok = false;
    const auto hash = core::crypto::sha256_file(localPath.toStdString(), ok);
    if (!ok) {
        result["ok"] = false;
        result["error"] = "Hash failed";
        return result;
    }
    const auto hash_hex = core::crypto::to_hex(hash);
    const auto txs = tx_store_->find_by_hash(hash_hex);
    if (txs.empty()) {
        result["ok"] = false;
        result["error"] = "Transaction not found";
        result["hash"] = QString::fromStdString(hash_hex);
        return result;
    }
    const auto& tx = txs.front();
    result["ok"] = true;
    result["hash"] = QString::fromStdString(tx.file_hash);
    result["sender"] = QString::fromStdString(tx.sender);
    result["receiver"] = QString::fromStdString(tx.receiver);
    result["blockIndex"] = static_cast<qint64>(tx.block_index);
    result["fileName"] = QString::fromStdString(tx.file_name);
    return result;
}

void AppController::load_models() {
    if (user_store_) {
        const auto list = user_store_->list_users();
        QVector<UserItem> users;
        users.reserve(static_cast<int>(list.size()));
        for (const auto& u : list) {
            users.push_back({QString::fromStdString(u.name),
                             QString::fromStdString(u.address_hex),
                             QString::fromStdString(u.host),
                             static_cast<int>(u.port)});
        }
        users_.setItems(std::move(users));
    }
    if (tx_store_) {
        const auto list = tx_store_->list();
        QVector<TxItem> txs;
        txs.reserve(static_cast<int>(list.size()));
        for (const auto& t : list) {
            txs.push_back({QString::fromStdString(t.tx_id),
                           QString::fromStdString(t.sender),
                           QString::fromStdString(t.receiver),
                           QString::fromStdString(t.file_hash),
                           QString::fromStdString(t.file_name),
                           static_cast<qint64>(t.file_size),
                           QString::fromStdString(t.mime),
                           t.timestamp_ms,
                           t.block_index});
        }
        txs_.setItems(std::move(txs));
    }
    if (block_store_) {
        const auto list = block_store_->list();
        QVector<BlockItem> blocks;
        blocks.reserve(static_cast<int>(list.size()));
        for (const auto& b : list) {
            blocks.push_back({QString::fromStdString(b.hash),
                              QString::fromStdString(b.previous_hash),
                              b.timestamp_ms,
                              QString::fromStdString(b.authority)});
        }
        blocks_.setItems(std::move(blocks));
    }
}

void AppController::process_mempool() {
    if (!current_user_ || !blockchain_) {
        return;
    }
    std::vector<core::Transaction> batch;
    while (auto tx = mempool_.pop()) {
        batch.push_back(std::move(*tx));
    }
    if (batch.empty()) {
        return;
    }
    auto block = blockchain_->create_block(batch, current_user_->private_key());
    const auto block_index = static_cast<std::int64_t>(blockchain_->chain().size());
    blockchain_->add_block(block);

    storage::StoredBlock stored_block;
    stored_block.hash = core::crypto::to_hex(block.hash());
    stored_block.previous_hash = core::crypto::to_hex(block.previous_hash());
    stored_block.timestamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                                    block.created_at().time_since_epoch()).count();
    stored_block.authority = core::crypto::to_hex(block.authority());
    block_store_->add(stored_block);

    for (const auto& tx : block.transactions()) {
        storage::StoredTransaction stored;
        stored.tx_id = core::crypto::to_hex(tx.id());
        stored.sender = core::crypto::to_hex(tx.sender());
        stored.receiver = core::crypto::to_hex(tx.receiver());
        stored.file_hash = core::crypto::to_hex(tx.file_hash());
        stored.file_name = tx.metadata().name;
        stored.file_size = tx.metadata().size;
        stored.mime = tx.metadata().mime;
        stored.block_index = block_index;
        stored.timestamp_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                                  tx.created_at().time_since_epoch()).count();
        tx_store_->add(stored);
    }
    load_models();
}

void AppController::on_file_received(const network::ReceivedFile& file) {
    try {
        const auto sender_hex = core::crypto::to_hex(file.sender);
        const auto sender = user_store_->find_by_address(sender_hex);
        if (sender.empty()) {
            emit notification("Файл получен, но отправитель не зарегистрирован");
            core::log::write(core::log::Level::Warn, "Unknown sender: " + sender_hex);
            return;
        }
        core::Transaction tx = core::Transaction::deserialize(file.tx_payload);
        if (!tx.verify(sender.front().public_key)) {
            emit notification("Получена транзакция с неверной подписью");
            core::log::write(core::log::Level::Warn, "Invalid transaction signature");
            return;
        }
        mempool_.push(tx);
        process_mempool();
        emit notification("Файл получен и подтвержден");
        core::log::write(core::log::Level::Info, "File received and added to chain");
    } catch (...) {
        emit notification("Ошибка обработки входящего файла");
        core::log::write(core::log::Level::Error, "File receive handling failed");
    }
}

void AppController::restart_node(const QString& host, int port) {
    if (!node_) {
        return;
    }
    if (node_->port() == static_cast<std::uint16_t>(port)) {
        return;
    }
    node_->stop();
    const auto files_dir = data_dir_ + "/files";
    node_ = std::make_unique<network::Node>(host.toStdString(),
                                            static_cast<std::uint16_t>(port),
                                            files_dir.toStdString());
    node_->set_on_file_received([this](const network::ReceivedFile& file) { on_file_received(file); });
    node_->start();
    if (!node_->last_error().empty()) {
        core::log::write(core::log::Level::Error, "Node restart failed: " + node_->last_error());
        emit notification(QString::fromStdString("Ошибка запуска узла: " + node_->last_error()));
        return;
    }
    core::log::write(core::log::Level::Info, "Node restarted on " + host.toStdString() + ":" + std::to_string(port));
}
