#include "message.h"

Message::Message() : message_size(0) {

    message_byte_array.clear();

}

Message::Message(const size_t &message_size, Connection* sender) : message_size(message_size),
                                                                   sender(sender) {

    message_byte_array.clear();

}

Message::Message(const size_t &message_size,
                 const QByteArray &message_byte_array,
                 Connection* sender) : message_size(message_size),
                                       message_byte_array(message_byte_array),
                                       sender(sender) {}

Message::Message(Message &&other) : message_size(other.message_size),
                                    message_byte_array(std::move(other.message_byte_array)),
                                    sender(other.sender) {

    other.message_size = 0;
    other.sender = nullptr;

}

void Message::SetMessageData(const size_t &message_size, const QByteArray &message_byte_array, Connection* &sender) {

    this->message_size = message_size;
    this->message_byte_array = message_byte_array;
    this->sender = sender;

}

void Message::SetSize(const size_t &message_size) {

    this->message_size = message_size;

}

void Message::SetSender(Connection *sender) {

    this->sender = sender;

}

size_t Message::GetSize() {

    return message_size;

}

QByteArray Message::GetMessageByteArray() {

    return message_byte_array;

}

void Message::AppendToMessageByteArray(const QByteArray &byte_array) {

    message_byte_array.append(byte_array);

}

bool Message::IsReady() {

    return (message_byte_array.size() == message_size) && message_size != 0;

}

Connection* Message::GetSender() {

    return sender;

}
