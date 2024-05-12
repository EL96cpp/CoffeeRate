#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtXml>
#include <QDebug>
#include <thread>

#include "message.h"
#include "threadsafelist.h"

class Client : public QObject {

    Q_OBJECT
public:
    Client(QObject *parent = nullptr);

    void ConnectToServer(const QString& address, const quint16& port);

signals:
    void errorMessage(const QString& error_title, const QString& error_description);

public slots:
    void onLogin(const QString& nickname, const QString& password);
    void onRegister(const QString& nickname, const QString& password);
    void onReadyRead();

private:
    void ProcessMessages();
    void RespondToMessage(const QByteArray& message_byte_array);

private:
    QTcpSocket* socket;
    std::thread message_processing_thread;
    std::shared_ptr<Message> temporary_message;
    ThreadSafeList<Message> incoming_messages;

};

#endif // CLIENT_H
