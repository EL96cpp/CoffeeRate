#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtXml>


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

signals:

public slots:
    void onLogin(const QString& nickname, const QString& password);
    void onRegister(const QString& nickname, const QString& password);


private:
    QTcpSocket* socket;

};

#endif // CLIENT_H
