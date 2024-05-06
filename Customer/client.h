#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtXml>
#include <QDebug>


class Client : public QObject {

    Q_OBJECT
public:
    Client(QObject *parent = nullptr);

signals:

public slots:
    void onLogin(const QString& nickname, const QString& password);
    void onRegister(const QString& nickname, const QString& password);
    void onReadyRead();

private:
    QTcpSocket* socket;

};

#endif // CLIENT_H
