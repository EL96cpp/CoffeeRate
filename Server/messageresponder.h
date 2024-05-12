#ifndef MESSAGERESPONDER_H
#define MESSAGERESPONDER_H

#include <QObject>
#include <QRunnable>
#include <QByteArray>
#include <QtXml>

#include "threadsafelist.h"
#include "connection.h"
#include "message.h"
#include "sqlservice.h"

class MessageResponder : public QRunnable {

public:
    MessageResponder(ThreadSafeList<Message>& incoming_messages, ThreadSafeList<Connection>& connections,
                     std::atomic<unsigned long long>& sql_connections_counter);

    void run() override;

private:
    void RespondToMessage(std::shared_ptr<Message>& message);
    QByteArray Login(const QString& nickname, const QString& password);
    QByteArray Register(const QString& nickname, const QString& password);

private:
    std::atomic<unsigned long long>& sql_connections_counter;
    ThreadSafeList<Message>& incoming_messages;
    ThreadSafeList<Connection>& connections;
    SqlService* sql_service;

};

#endif // MESSAGERESPONDER_H
