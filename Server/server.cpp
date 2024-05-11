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

    while (true) {

        incoming_messages.wait();

        while (!incoming_messages.empty()) {

            qDebug() << "incoming message processing!";

            auto message = incoming_messages.pop_back();

            RespondToMessage(std::move(message));

        }

    }

}

void Server::RespondToMessage(std::shared_ptr<Message>&& message) {

    QByteArray message_byte_array = message->GetMessageByteArray();


    QDomDocument document;
    document.setContent(message_byte_array);

    QDomElement root = document.firstChildElement();

    QDomNodeList children_nodes = root.childNodes();

    qDebug() << children_nodes.at(0).toElement().attribute("Action");

    QDomElement login_data = children_nodes.at(1).toElement();

    qDebug() << login_data.attribute("Nickname") << " " << login_data.attribute("Password");


}
