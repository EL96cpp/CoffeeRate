#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);

    Server server;
    server.StartListening(8000);

    return a.exec();

}
