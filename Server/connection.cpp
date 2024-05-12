#include "connection.h"

Connection::Connection(QObject *parent, const quintptr& handler,
                       ThreadSafeList<Message>& incoming_messages) : QObject{parent},
                                                                     logged_in(false),
                                                                     socket(new QTcpSocket(this)),
                                                                     incoming_messages(incoming_messages) {

    socket->setSocketDescriptor(handler);

    temporary_message = std::make_shared<Message>(this);

    connect(socket, &QTcpSocket::readyRead, this, &Connection::OnReadyRead);

}

void Connection::SetNickname(const QString &nickname) {

    this->nickname = nickname;

}

QString Connection::GetNickname() {

    return nickname;

}

bool Connection::IsLoggedIn() {

    return logged_in;

}

void Connection::SendMessage(Message &message) {

    qDebug() << "Send message call!";

    QByteArray byte_array = message.GetMessageByteArray();
    byte_array.prepend(QString::number(message.GetSize()).toUtf8() + "\n");

}

void Connection::SendMessage(const QByteArray &message) {

    qDebug() << "Send message call!";

    socket->write(message);

    qDebug() << "Send message call ended!";

}

void Connection::OnReadyRead() {

    if (temporary_message->GetSize() == 0) {

        QByteArray size_byte_array = socket->readLine();
        size_byte_array.removeLast();
        size_t message_size = size_byte_array.toInt();

        if (socket->bytesAvailable() != 0) {

            QByteArray message_byte_array = socket->read(socket->bytesAvailable());

            temporary_message = std::make_shared<Message>(message_size, message_byte_array, this);

            if (temporary_message->IsReady()) {

                incoming_messages.push_front(temporary_message);
                temporary_message = std::make_shared<Message>(this);

            }

        }

    } else {

        if (temporary_message->IsReady()) {

            incoming_messages.push_front(temporary_message);
            temporary_message = std::make_shared<Message>(this);

        } else {

            QByteArray new_array = socket->read(socket->bytesAvailable());

            temporary_message->AppendToMessageByteArray(new_array);

            if (temporary_message->IsReady()) {

                incoming_messages.push_front(temporary_message);
                temporary_message = std::make_shared<Message>(this);

            }

        }

    }

}
