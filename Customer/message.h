#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QDebug>

class Connection;

class Message {

public:
    Message();
    Message(const size_t& message_size);
    Message(const size_t& message_size, const QByteArray& message_byte_array);
    Message(Message&& other);
    Message(const Message& other);

    void SetMessageData(const size_t &message_size, const QByteArray &message_byte_array);
    void SetSize(const size_t& message_size);
    size_t GetSize();
    QByteArray GetMessageByteArray();
    void AppendToMessageByteArray(const QByteArray& byte_array);
    bool IsReady();

private:
    size_t message_size;
    QByteArray message_byte_array;

};

#endif // MESSAGE_H
