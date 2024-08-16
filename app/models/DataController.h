#pragma once

#include <QObject>
#include <QList>
#include <QVariantList>
#include <QSharedPointer>
#include "folder.h"

class DataController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList foldersModel READ foldersModel NOTIFY foldersModelChanged)

public:
    explicit DataController(QObject *parent = nullptr);

    Q_INVOKABLE void addFolder(const QString &name);
    Q_INVOKABLE void selectFolder(int index);

    QVariantList foldersModel() const;

signals:
    void foldersModelChanged();

private:
    QList<QSharedPointer<Folder>> m_folders;
    QVariantList m_foldersModel;

    void updateFoldersModel();
};
