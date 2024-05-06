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
    Connection(QObject *parent, const quintptr& handler, ThreadSafeList<Message>& incoming_messages);

    void SetNickname(const QString& nickname);

    QString GetNickname();
    bool IsLoggedIn();
    void SendMessage(Message& message);

signals:


private slots:
    void OnReadyRead();


private:
    QString nickname;
    QTcpSocket* socket;
    bool logged_in;
    ThreadSafeList<Message>& incoming_messages;
    std::shared_ptr<Message> temporary_message;

};

#endif // CONNECTION_H
