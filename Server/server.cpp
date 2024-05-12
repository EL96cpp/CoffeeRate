#include "server.h"

Server::Server() {

    QThreadPool::globalInstance()->setMaxThreadCount(10);

}

void Server::StartListening(const quint16 &port) {

    if (listen(QHostAddress::Any, port)) {

        qDebug() << "Start listening on port " << port;

    } else {

        qDebug() << "Start listening error! Port: " << port;

    }

}

void Server::incomingConnection(qintptr handle) {

    qDebug() << "Incoming connection";
    std::shared_ptr<Connection> connection = std::make_shared<Connection>(this, handle, sql_connections_counter, connections);
    connections.push_front(std::move(connection));

    ++sql_connections_counter;

}
