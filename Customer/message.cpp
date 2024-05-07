#include "message.h"

Message::Message() : message_size(0) {

    message_byte_array.clear();

}

Message::Message(const size_t &message_size) : message_size(message_size) {

    message_byte_array.clear();

}

Message::Message(const size_t &message_size,
                 const QByteArray &message_byte_array) : message_size(message_size),
                                                         message_byte_array(message_byte_array) {}

Message::Message(Message &&other) : message_size(other.message_size),
                                    message_byte_array(std::move(other.message_byte_array)) {

    other.message_size = 0;

}

void Message::SetMessageData(const size_t &message_size, const QByteArray &message_byte_array) {

    this->message_size = message_size;
    this->message_byte_array = message_byte_array;

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
