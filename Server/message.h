#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>

#include "connection.h"

class Message {

public:
    Message(const size_t& message_size, const QByteArray& message_byte_array);

    size_t GetSize();
    QByteArray GetMessageByteArray();
    bool IsReady();

private:
    size_t message_size;
    QByteArray message_byte_array;

};

#endif // MESSAGE_H
