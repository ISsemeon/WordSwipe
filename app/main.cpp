#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "models/dataController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DataController dataController;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataController", &dataController);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
