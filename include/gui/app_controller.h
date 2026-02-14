#ifndef BLOCKCHAIN_GUI_APP_CONTROLLER_H
#define BLOCKCHAIN_GUI_APP_CONTROLLER_H

#include "gui/models.h"
#include "core/blockchain.h"
#include "core/mempool.h"
#include "core/user.h"
#include "network/node.h"
#include "storage/database.h"
#include "storage/user_store.h"
#include "storage/tx_store.h"
#include "storage/block_store.h"

#include <QObject>
#include <QString>
#include <QTimer>
#include <QVariantMap>

class AppController : public QObject {
    Q_OBJECT
    Q_PROPERTY(UserListModel* users READ users CONSTANT)
    Q_PROPERTY(TxListModel* transactions READ transactions CONSTANT)
    Q_PROPERTY(BlockListModel* blocks READ blocks CONSTANT)
    Q_PROPERTY(QString currentUserName READ currentUserName NOTIFY currentUserChanged)
    Q_PROPERTY(QString currentUserAddress READ currentUserAddress NOTIFY currentUserChanged)
public:
    explicit AppController(QObject* parent = nullptr);
    ~AppController() override;

    UserListModel* users() { return &users_; }
    TxListModel* transactions() { return &txs_; }
    BlockListModel* blocks() { return &blocks_; }

    QString currentUserName() const;
    QString currentUserAddress() const;

    Q_INVOKABLE bool initialize(const QString& dataDir, const QString& host, int port);
    Q_INVOKABLE bool initializeDefault(const QString& host, int port);
    Q_INVOKABLE bool registerUser(const QString& name, const QString& host, int port, QString& error);
    Q_INVOKABLE bool loginByAddress(const QString& address, QString& error);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE bool sendFile(const QString& receiverAddress, const QString& filePath, QString& error);
    Q_INVOKABLE QVariantMap verifyFile(const QString& filePath);

signals:
    void currentUserChanged();
    void notification(const QString& message);

private:
    void load_models();
    void process_mempool();
    void on_file_received(const network::ReceivedFile& file);
    void restart_node(const QString& host, int port);

    std::unique_ptr<storage::Database> db_;
    std::unique_ptr<storage::UserStore> user_store_;
    std::unique_ptr<storage::TxStore> tx_store_;
    std::unique_ptr<storage::BlockStore> block_store_;

    std::unique_ptr<core::User> current_user_;
    std::unique_ptr<core::Blockchain> blockchain_;
    core::Mempool mempool_;

    std::unique_ptr<network::Node> node_;

    UserListModel users_;
    TxListModel txs_;
    BlockListModel blocks_;

    QTimer mempool_timer_;
    QString data_dir_;
};

#endif
