#include "SessionManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

bool SessionManager::saveSession(const QString &filePath, const QList<QSharedPointer<Folder>> &folders) {
    QJsonArray jsonArray;
    for (const auto &folder : folders) {
        jsonArray.append(serializeFolder(folder));
    }

    QJsonObject sessionObject;
    sessionObject["folders"] = jsonArray;
    sessionObject["lastSession"] = QDateTime::currentDateTime().toString(Qt::ISODate); // Save the last session date

    QJsonDocument doc(sessionObject);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << file.errorString();
        return false;
    }

    file.write(doc.toJson());
    return true;
}

bool SessionManager::loadSession(const QString &filePath, QList<QSharedPointer<Folder>> &folders) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file for reading:" << file.errorString();
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject sessionObject = doc.object();

    if (sessionObject.contains("folders")) {
        QJsonArray jsonArray = sessionObject["folders"].toArray();
        folders.clear();
        for (const QJsonValue &value : jsonArray) {
            QSharedPointer<Folder> folder = deserializeFolder(value.toObject());
            folders.append(folder);
        }
    }

    // Optionally handle the last session date
    if (sessionObject.contains("lastSession")) {
        QString lastSessionDate = sessionObject["lastSession"].toString();
        qDebug() << "Last session date:" << lastSessionDate;
    }

    return true;
}
bool SessionManager::exportFolder(const QString &filePath, const QSharedPointer<Folder> &folder) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << file.errorString();
        return false;
    }

    QJsonObject folderObj = serializeFolder(folder);

    QJsonObject rootObj;
    rootObj["folder"] = folderObj;
    rootObj["exported"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonDocument doc(rootObj);
    file.write(doc.toJson());
    return true;
}

bool SessionManager::importFolder(const QString &filePath, QSharedPointer<Folder> &folder) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file for reading:" << file.errorString();
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = doc.object();

    QJsonObject folderObj = rootObj["folder"].toObject();
    folder = deserializeFolder(folderObj);

    QString exportedDate = rootObj["exported"].toString();
    qDebug() << "Folder exported on:" << exportedDate;

    return true;
}

bool SessionManager::exportModule(const QString &filePath, const QSharedPointer<Module> &module) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << file.errorString();
        return false;
    }

    QJsonObject moduleObj = serializeModule(module);

    QJsonObject rootObj;
    rootObj["module"] = moduleObj;
    rootObj["exported"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonDocument doc(rootObj);
    file.write(doc.toJson());
    return true;
}

bool SessionManager::importModule(const QString &filePath, QSharedPointer<Module> &module) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file for reading:" << file.errorString();
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = doc.object();

    QJsonObject moduleObj = rootObj["module"].toObject();
    module = deserializeModule(moduleObj);

    QString exportedDate = rootObj["exported"].toString();
    qDebug() << "Module exported on:" << exportedDate;

    return true;
}

QJsonObject SessionManager::serializeFolder(const QSharedPointer<Folder> &folder) {
    QJsonObject folderObj;
    folderObj["name"] = folder->name();

    QJsonArray modulesArray;
    for (const auto &module : folder->modulesModel()->modules()) {
        modulesArray.append(serializeModule(module));
    }
    folderObj["modules"] = modulesArray;

    return folderObj;
}

QJsonObject SessionManager::serializeModule(const QSharedPointer<Module> &module) {
    QJsonObject moduleObj;
    moduleObj["name"] = module->name();
    moduleObj["color"] = module->color();

    QJsonArray cardsArray;
    for (const auto &card : module->cardsModel()->cards()) {
        cardsArray.prepend(serializeCard(card));
    }
    moduleObj["cards"] = cardsArray;

    return moduleObj;
}

QJsonObject SessionManager::serializeCard(const QSharedPointer<Card> &card) {
    QJsonObject cardObj;
    cardObj["question"] = card->question();
    cardObj["answer"] = card->answer();
    return cardObj;
}

QSharedPointer<Folder> SessionManager::deserializeFolder(const QJsonObject &json) {
    QSharedPointer<Folder> folder(new Folder());
    folder->setName(json["name"].toString());

    QJsonArray modulesArray = json["modules"].toArray();
    for (const QJsonValue &moduleValue : modulesArray) {
        QSharedPointer<Module> module = deserializeModule(moduleValue.toObject());
        folder->modulesModel()->addModule(module);
    }

    return folder;
}

QSharedPointer<Module> SessionManager::deserializeModule(const QJsonObject &json) {
    QSharedPointer<Module> module(new Module());
    module->setName(json["name"].toString());
    module->setColor(json["color"].toString());

    QJsonArray cardsArray = json["cards"].toArray();
    for (const QJsonValue &cardValue : cardsArray) {
        QSharedPointer<Card> card = deserializeCard(cardValue.toObject());
        module->cardsModel()->addCard(card);
    }

    return module;
}

QSharedPointer<Card> SessionManager::deserializeCard(const QJsonObject &json) {
    QSharedPointer<Card> card(new Card(json["question"].toString(), json["answer"].toString()));
    return card;
}
