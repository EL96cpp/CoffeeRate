#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtXml>
#include <thread>
#include <atomic>

#include "sqlservice.h"
#include "connection.h"
#include "threadsafelist.h"
#include "message.h"
#include "messageresponder.h"


class Server : public QTcpServer {
    Q_OBJECT
public:
    Server();

    Server(const Server& other) = delete;
    Server& operator = (const Server& other) = delete;

    void StartListening(const quint16& port);

private:
    void incomingConnection(qintptr handle);

private:
    std::atomic<unsigned long long> sql_connections_counter;
    std::thread message_processing_thread2;
    QThread message_processing_thread;
    ThreadSafeList<Connection> connections;
    ThreadSafeList<Message> incoming_messages;

};

#endif // SERVER_H
