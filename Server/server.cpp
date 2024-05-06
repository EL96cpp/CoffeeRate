#include "server.h"

Server::Server() {}

void Server::incomingConnection(qintptr handle) {

    std::shared_ptr<Connection> connection = std::make_shared<Connection>(this, handle, incoming_messages);
    connections.push_front(std::move(connection));

    message_processing_thread = std::thread([](){});

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
