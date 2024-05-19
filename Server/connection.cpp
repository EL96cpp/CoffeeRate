#include "connection.h"

Connection::Connection(QObject *parent,
                       const quintptr& handler,
                       std::atomic<unsigned long long>& sql_connections_counter,
                       ThreadSafeList<Connection>& connections) : QObject{parent},
                                                                  logged_in(false),
                                                                  socket(new QTcpSocket(this)),
                                                                  connections(connections),
                                                                  sql_connections_counter(sql_connections_counter) {

    socket->setSocketDescriptor(handler);
    temporary_message = std::make_shared<Message>();
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

void Connection::SendMessage(const QByteArray &message_byte_array) {

    qDebug() << "Send message call!";

    qDebug() << message_byte_array;

    socket->write(message_byte_array);

    qDebug() << "Send message call ended!";

}


void Connection::OnReadyRead() {

    if (temporary_message->GetSize() == 0) {


        QByteArray size_byte_array = socket->readLine();
        size_byte_array.removeLast();
        size_t message_size = size_byte_array.toInt();

        if (socket->bytesAvailable() != 0) {

            QByteArray message_byte_array = socket->read(socket->bytesAvailable());

            temporary_message = std::make_shared<Message>(message_size, message_byte_array);

            if (temporary_message->IsReady()) {

                MessageResponder* message_responder = new MessageResponder(this, temporary_message->GetMessageByteArray(),
                                                                           connections, sql_connections_counter);

                connect(message_responder, &MessageResponder::MessageResponceIsReady, this, &Connection::SendMessage);

                QThreadPool::globalInstance()->start(message_responder);

                ++sql_connections_counter;
                temporary_message = std::make_shared<Message>();

            }

        }

    } else {

        if (temporary_message->IsReady()) {

            MessageResponder* message_responder = new MessageResponder(this, temporary_message->GetMessageByteArray(),
                                                                       connections, sql_connections_counter);

            connect(message_responder, &MessageResponder::MessageResponceIsReady, this, &Connection::SendMessage);

            QThreadPool::globalInstance()->start(message_responder);

            ++sql_connections_counter;
            temporary_message = std::make_shared<Message>();

        } else {

            QByteArray new_array = socket->read(socket->bytesAvailable());

            temporary_message->AppendToMessageByteArray(new_array);

            if (temporary_message->IsReady()) {

                MessageResponder* message_responder = new MessageResponder(this, temporary_message->GetMessageByteArray(),
                                                                           connections, sql_connections_counter);

                connect(message_responder, &MessageResponder::MessageResponceIsReady, this, &Connection::SendMessage);

                QThreadPool::globalInstance()->start(message_responder);

                ++sql_connections_counter;
                temporary_message = std::make_shared<Message>();

            }

        }

    }

}
