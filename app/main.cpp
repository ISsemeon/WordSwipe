#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "models/DataController.h"
#include "models/SessionManager.h"
#include <QStandardPaths>

QString getSessionFilePath() {
    // Path for storing the file on mobile devices
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/session.json";
    #else
        return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/session.json";
    #endif
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DataController dataController;
    QString sessionFilePath = getSessionFilePath();

    // Load session
    QList<QSharedPointer<Folder>> folders;
    if (SessionManager::loadSession(sessionFilePath, folders)) {
        dataController.setFolders(folders);
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataController", &dataController);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    int ret = app.exec();

    // Save session on application quit
    QList<QSharedPointer<Folder>> foldersToSave = dataController.getFolders();
    SessionManager::saveSession(sessionFilePath, foldersToSave);

    return ret;
}
