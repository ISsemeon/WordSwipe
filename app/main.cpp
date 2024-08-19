#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "models/DataController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DataController dataController;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataController", &dataController);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}
