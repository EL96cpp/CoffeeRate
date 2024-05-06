#include "server.h"

Server::Server() {}

void Server::ProcessMessages() {

    incoming_messages.wait();

    while (!incoming_messages.empty()) {

        auto message = incoming_messages.pop_back();

        RespondToMessage(std::move(message));

    }

}

void Server::RespondToMessage(std::shared_ptr<Message>&& message) {



}
