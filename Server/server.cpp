#include "server.h"

Server::Server() {

    message_processing_thread = std::thread(&Server::ProcessMessages, this);
    message_processing_thread.detach();

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
    std::shared_ptr<Connection> connection = std::make_shared<Connection>(this, handle, incoming_messages);
    connections.push_front(std::move(connection));

}


void Server::ProcessMessages() {

    incoming_messages.wait();

    while (!incoming_messages.empty()) {

        auto message = incoming_messages.pop_back();

        RespondToMessage(std::move(message));

    }

}

void Server::RespondToMessage(std::shared_ptr<Message>&& message) {



}
