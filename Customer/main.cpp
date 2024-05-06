#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "client.h"

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Customer/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    Client client;
    client.ConnectToServer("127.0.0.1", 8000);

    return app.exec();

}
