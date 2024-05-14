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

class MessageResponder : public QObject, public QRunnable {

    Q_OBJECT

public:
    MessageResponder(QObject* parent, const QByteArray& incoming_message, ThreadSafeList<Connection>& connections,
                     std::atomic<unsigned long long>& sql_connections_counter);

    void run() override;

signals:
    void MessageResponceIsReady(const QByteArray& message_byte_array);

private:
    void Login(const QString& nickname, const QString& password);
    void Register(const QString& nickname, const QString& password);
    void SendCafeReviews(const int& cafe_id);
    void SendAllCafeObjects();

private:
    std::atomic<unsigned long long>& sql_connections_counter;
    QByteArray incoming_message;
    ThreadSafeList<Connection>& connections;
    SqlService* sql_service;

};

#endif // MESSAGERESPONDER_H
