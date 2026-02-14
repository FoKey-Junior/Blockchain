#ifndef BLOCKCHAIN_GUI_MODELS_H
#define BLOCKCHAIN_GUI_MODELS_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>

struct UserItem {
    QString name;
    QString address;
    QString host;
    int port;
};

struct TxItem {
    QString txId;
    QString sender;
    QString receiver;
    QString fileHash;
    QString fileName;
    qint64 fileSize;
    QString mime;
    qint64 timestampMs;
    qint64 blockIndex;
};

struct BlockItem {
    QString hash;
    QString prevHash;
    qint64 timestampMs;
    QString authority;
};

class UserListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles { NameRole = Qt::UserRole + 1, AddressRole, HostRole, PortRole };
    explicit UserListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setItems(QVector<UserItem> items);
    const QVector<UserItem>& items() const { return items_; }

private:
    QVector<UserItem> items_;
};

class TxListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles {
        TxIdRole = Qt::UserRole + 1, SenderRole, ReceiverRole, FileHashRole,
        FileNameRole, FileSizeRole, MimeRole, TimestampRole, BlockIndexRole
    };
    explicit TxListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setItems(QVector<TxItem> items);
    const QVector<TxItem>& items() const { return items_; }

private:
    QVector<TxItem> items_;
};

class BlockListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles { HashRole = Qt::UserRole + 1, PrevHashRole, TimestampRole, AuthorityRole };
    explicit BlockListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setItems(QVector<BlockItem> items);

private:
    QVector<BlockItem> items_;
};

#endif
