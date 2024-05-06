#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>

class Connection;

class Message {

public:
    Message();
    Message(const size_t& message_size, const QByteArray& message_byte_array, Connection* sender);
    Message(Message&& other);

    void SetMessageData(const size_t &message_size, const QByteArray &message_byte_array, Connection* &sender);
    size_t GetSize();
    QByteArray GetMessageByteArray();
    void AppendToMessageByteArray(const QByteArray& byte_array);
    bool IsReady();
    Connection* GetSender();

private:
    size_t message_size;
    QByteArray message_byte_array;
    Connection* sender;

};

#endif // MESSAGE_H
