#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client.h"

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    Client client;
    client.ConnectToServer("127.0.0.1", 8000);

    QQmlApplicationEngine engine;
    QQmlContext* root_context = engine.rootContext();
    root_context->setContextProperty("Client", &client);

    const QUrl url(u"qrc:/Customer/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();

}
