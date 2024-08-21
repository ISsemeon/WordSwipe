#include "FolderModel.h"

FolderModel::FolderModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int FolderModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_folders.size();
}

QVariant FolderModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_folders.size()) {
        return QVariant();
    }

    const auto folder = m_folders[index.row()];
    if (role == NameRole) {
        return folder->name();
    } else if (role == FolderRole) {  // Добавьте эту роль для возвращения указателя на папку
        return QVariant::fromValue(folder);
    }

    return QVariant();
}

QHash<int, QByteArray> FolderModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FolderRole] = "folder";
    return roles;
}

void FolderModel::addFolder(const QSharedPointer<Folder> &folder) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_folders.append(folder);
    endInsertRows();
}

void FolderModel::clear() {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_folders.clear();
    endRemoveRows();
}
