#include "message.h"

Message::Message(const size_t &message_size,
                 const QByteArray &message_byte_array) : message_size(message_size),
                                                         message_byte_array(message_byte_array) {}

size_t Message::GetSize() {

    return message_size;

}

QByteArray Message::GetMessageByteArray() {

    return message_byte_array;

}

bool Message::IsReady() {

    return message_byte_array.size() == message_size;

}
