#include "client.h"

Client::Client(QObject *parent)
    : QObject{parent}, socket(new QTcpSocket(this))
{}

void Client::onLogin(const QString &nickname, const QString &password) {



}

void Client::onRegister(const QString &nickname, const QString &password) {



}
