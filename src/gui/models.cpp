#include "gui/models.h"

UserListModel::UserListModel(QObject* parent) : QAbstractListModel(parent) {}

int UserListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return items_.size();
}

QVariant UserListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= items_.size()) {
        return {};
    }
    const auto& item = items_[index.row()];
    switch (role) {
        case NameRole: return item.name;
        case AddressRole: return item.address;
        case HostRole: return item.host;
        case PortRole: return item.port;
        default: return {};
    }
}

QHash<int, QByteArray> UserListModel::roleNames() const {
    return {
        {NameRole, "name"},
        {AddressRole, "address"},
        {HostRole, "host"},
        {PortRole, "port"}
    };
}

void UserListModel::setItems(QVector<UserItem> items) {
    beginResetModel();
    items_ = std::move(items);
    endResetModel();
}

TxListModel::TxListModel(QObject* parent) : QAbstractListModel(parent) {}

int TxListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return items_.size();
}

QVariant TxListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= items_.size()) {
        return {};
    }
    const auto& item = items_[index.row()];
    switch (role) {
        case TxIdRole: return item.txId;
        case SenderRole: return item.sender;
        case ReceiverRole: return item.receiver;
        case FileHashRole: return item.fileHash;
        case FileNameRole: return item.fileName;
        case FileSizeRole: return item.fileSize;
        case MimeRole: return item.mime;
        case TimestampRole: return item.timestampMs;
        case BlockIndexRole: return item.blockIndex;
        default: return {};
    }
}

QHash<int, QByteArray> TxListModel::roleNames() const {
    return {
        {TxIdRole, "txId"},
        {SenderRole, "sender"},
        {ReceiverRole, "receiver"},
        {FileHashRole, "fileHash"},
        {FileNameRole, "fileName"},
        {FileSizeRole, "fileSize"},
        {MimeRole, "mime"},
        {TimestampRole, "timestampMs"},
        {BlockIndexRole, "blockIndex"}
    };
}

void TxListModel::setItems(QVector<TxItem> items) {
    beginResetModel();
    items_ = std::move(items);
    endResetModel();
}

BlockListModel::BlockListModel(QObject* parent) : QAbstractListModel(parent) {}

int BlockListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return items_.size();
}

QVariant BlockListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= items_.size()) {
        return {};
    }
    const auto& item = items_[index.row()];
    switch (role) {
        case HashRole: return item.hash;
        case PrevHashRole: return item.prevHash;
        case TimestampRole: return item.timestampMs;
        case AuthorityRole: return item.authority;
        default: return {};
    }
}

QHash<int, QByteArray> BlockListModel::roleNames() const {
    return {
        {HashRole, "hash"},
        {PrevHashRole, "prevHash"},
        {TimestampRole, "timestampMs"},
        {AuthorityRole, "authority"}
    };
}

void BlockListModel::setItems(QVector<BlockItem> items) {
    beginResetModel();
    items_ = std::move(items);
    endResetModel();
}
