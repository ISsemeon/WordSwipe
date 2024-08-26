#pragma once

#include <QString>
#include <QJsonObject>
#include <QDateTime>
#include <QSharedPointer>
#include "folder.h"
#include "module.h"
#include "card.h"

class SessionManager {
public:
    static bool saveSession(const QString &filePath, const QList<QSharedPointer<Folder>> &folders);
    static bool loadSession(const QString &filePath, QList<QSharedPointer<Folder>> &folders);

    static bool exportFolder(const QString &filePath, const QSharedPointer<Folder> &folder);
    static bool importFolder(const QString &filePath, QSharedPointer<Folder> &folder);

    static bool exportModule(const QString &filePath, const QSharedPointer<Module> &module);
    static bool importModule(const QString &filePath, QSharedPointer<Module> &module);

private:
    static QJsonObject serializeFolder(const QSharedPointer<Folder> &folder);
    static QJsonObject serializeModule(const QSharedPointer<Module> &module);
    static QJsonObject serializeCard(const QSharedPointer<Card> &card);

    static QSharedPointer<Folder> deserializeFolder(const QJsonObject &json);
    static QSharedPointer<Module> deserializeModule(const QJsonObject &json);
    static QSharedPointer<Card> deserializeCard(const QJsonObject &json);
};
