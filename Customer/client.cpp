#include "client.h"

Client::Client(QObject *parent) : QObject{parent}, socket(new QTcpSocket(this)) {

    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);

}

void Client::ConnectToServer(const QString &address, const quint16 &port) {

    socket->connectToHost(address, port);

    socket->waitForConnected(3000);

    if (socket->state() != QAbstractSocket::ConnectedState) {

        emit errorMessage("Ошибка подключения", "Не удалось установить соединение с сервером");

    } else {

        qDebug() << "Connected!";

    }

}

void Client::onLogin(const QString &nickname, const QString &password) {

    QDomDocument message_document;

    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    QDomElement action = message_document.createElement("Action");
    action.setAttribute("Action", "Login");
    root.appendChild(action);

    QDomElement login_data = message_document.createElement("Login_data");
    login_data.setAttribute("Nickname", nickname);
    login_data.setAttribute("Password", password);
    root.appendChild(login_data);

    QByteArray message_byte_array = message_document.toByteArray();

    size_t message_size = message_byte_array.size();
    message_byte_array.prepend(QString::number(message_size).toUtf8() + "\n");

    qDebug() << message_byte_array;

    socket->write(message_byte_array);

}

void Client::onRegister(const QString &nickname, const QString &password) {

    QDomDocument message;

    QDomElement register_document = message.createElement("Register");
    message.appendChild(register_document);

    QDomElement node = message.createElement("Register_data");
    node.setAttribute("Nickname", nickname);
    node.setAttribute("Password", password);

    register_document.appendChild(node);

    QByteArray message_byte_array = message.toByteArray();

    size_t message_size = message_byte_array.size();
    message_byte_array.prepend(QString::number(message_size).toUtf8() + "\n");

    socket->write(message_byte_array);

}

void Client::onReadyRead() {

    if (temporary_message->GetSize() == 0) {

        QByteArray size_byte_array = socket->readLine();
        size_byte_array.removeLast();
        size_t message_size = size_byte_array.toInt();

        if (socket->bytesAvailable() != 0) {

            QByteArray message_byte_array = socket->readAll();

            temporary_message = std::make_shared<Message>(message_size, message_byte_array);

            if (temporary_message->IsReady()) {

                incoming_messages.push_front(std::move(temporary_message));

            }

        } else {

            temporary_message = std::make_shared<Message>(message_size);

        }

    } else {

        if (socket->bytesAvailable() != 0) {

            if (temporary_message->IsReady()) {

                incoming_messages.push_front(std::move(temporary_message));

                QByteArray size_byte_array = socket->readLine();
                size_byte_array.removeLast();
                size_t message_size = size_byte_array.toInt();

                temporary_message = std::make_shared<Message>(message_size);

            } else {

                QByteArray message_byte_array = socket->readAll();

                temporary_message->AppendToMessageByteArray(message_byte_array);

                if (temporary_message->IsReady()) {

                    incoming_messages.push_front(std::move(temporary_message));

                }

            }

        } else {

            if (temporary_message->IsReady()) {

                incoming_messages.push_front(std::move(temporary_message));

            }

        }

    }

}

void Client::ProcessMessages() {

    while (true) {

        incoming_messages.wait();

        while (!incoming_messages.empty()) {

            qDebug() << "incoming message processing!";

            auto message = incoming_messages.pop_back();

            RespondToMessage(message->GetMessageByteArray());

        }

    }

}

void Client::RespondToMessage(const QByteArray &message_byte_array) {

    qDebug() << message_byte_array;

}
