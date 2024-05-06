#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>

class Connection : public QObject {

    Q_OBJECT
public:
    Connection(QObject *parent = nullptr);

    void SetNickname(const QString& nickname);

    QString GetNickname();
    bool IsLoggedIn();

signals:


private:
    QString nickname;
    QTcpSocket* socket;
    bool logged_in;

};

#endif // CONNECTION_H
