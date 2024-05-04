#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtXml>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
};

#endif // SERVER_H
