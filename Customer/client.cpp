#include "client.h"

Client::Client(QObject *parent) : QObject{parent}, socket(new QTcpSocket(this)) {

    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);

}

void Client::onLogin(const QString &nickname, const QString &password) {

    QDomDocument message;

    QDomElement login_document = message.createElement("Login");
    message.appendChild(login_document);

    QDomElement node = message.createElement("Login_data");
    node.setAttribute("Nickname", nickname);
    node.setAttribute("Password", password);

    login_document.appendChild(node);

    socket->write(message.toByteArray());

}

void Client::onRegister(const QString &nickname, const QString &password) {

    QDomDocument message;

    QDomElement register_document = message.createElement("Register");
    message.appendChild(register_document);

    QDomElement node = message.createElement("Register_data");
    node.setAttribute("Nickname", nickname);
    node.setAttribute("Password", password);

    register_document.appendChild(node);

    socket->write(message.toByteArray());

}

void Client::onReadyRead() {


}
