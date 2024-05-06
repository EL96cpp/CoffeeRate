#include "connection.h"

Connection::Connection(QObject *parent) : QObject{parent}, socket(new QTcpSocket(this)), logged_in(false) {}

void Connection::SetNickname(const QString &nickname) {

    this->nickname = nickname;

}

QString Connection::GetNickname() {

    return nickname;

}

bool Connection::IsLoggedIn() {

    return logged_in;

}
