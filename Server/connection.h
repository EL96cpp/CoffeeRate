#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <memory>

#include "threadsafelist.h"
#include "message.h"

class Connection : public QObject {

    Q_OBJECT
public:
    Connection(QObject *parent, const quintptr& handler, std::atomic<unsigned long long>& sql_connections_counter);

    Connection(Connection& other) = delete;

    void SetNickname(const QString& nickname);

    QString GetNickname();
    bool IsLoggedIn();

signals:

public slots:
    void SendMessage(const QByteArray& message_byte_array);

private slots:
    void OnReadyRead();


private:
    QString nickname;
    QTcpSocket* socket;
    bool logged_in;
    std::atomic<unsigned long long>& sql_connections_counter;
    ThreadSafeList<Message> incoming_messages;
    std::shared_ptr<Message> temporary_message;

};

#endif // CONNECTION_H
