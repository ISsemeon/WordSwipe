#pragma once

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QList>
#include "folder.h"

class FolderModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        FolderRole
    };

    explicit FolderModel(QObject *parent = nullptr);

    // QAbstractListModel methods
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Methods for manipulating the model
    void addFolder(const QSharedPointer<Folder> &folder);
    void clear();

private:
    QList<QSharedPointer<Folder>> m_folders;
};
