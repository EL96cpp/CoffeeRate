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

    void ConnectToServer(const QString& address, const quint16& port);

signals:
    void errorMessage(const QString& error_title, const QString& error_description);

public slots:
    void onLogin(const QString& nickname, const QString& password);
    void onRegister(const QString& nickname, const QString& password);
    void onReadyRead();

private:
    QTcpSocket* socket;

};

#endif // CLIENT_H
