#include "client.h"

Client::Client(QObject *parent) : QObject{parent}, socket(new QTcpSocket(this)) {

    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);

    temporary_message = std::make_shared<Message>();

    message_processing_thread = std::thread(&Client::ProcessMessages, this);
    message_processing_thread.detach();

}

void Client::ConnectToServer(const QString &address, const quint16 &port) {

    socket->connectToHost(address, port);

    socket->waitForConnected(3000);

    if (socket->state() != QAbstractSocket::ConnectedState) {

        emit showMessage("Ошибка подключения", "Не удалось установить соединение с сервером");

    } else {

        qDebug() << "Connected!";

    }

}

void Client::onLogin(const QString &nickname, const QString &password) {

    QDomDocument message_document;

    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    QDomElement theme = message_document.createElement("Theme");
    theme.setAttribute("Theme", "Login");
    root.appendChild(theme);

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

    QDomDocument message_document;

    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    QDomElement theme = message_document.createElement("Theme");
    theme.setAttribute("Theme", "Register");
    root.appendChild(theme);

    QDomElement login_data = message_document.createElement("Register_data");
    login_data.setAttribute("Nickname", nickname);
    login_data.setAttribute("Password", password);
    root.appendChild(login_data);

    QByteArray message_byte_array = message_document.toByteArray();

    size_t message_size = message_byte_array.size();
    message_byte_array.prepend(QString::number(message_size).toUtf8() + "\n");

    qDebug() << message_byte_array;

    socket->write(message_byte_array);

}

void Client::onGetCafeReviews(const int &cafe_id) {

    QDomDocument message_document;

    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    QDomElement theme = message_document.createElement("Theme");
    theme.setAttribute("Theme", "Get_reviews");
    root.appendChild(theme);

    QDomElement cafe_id_element = message_document.createElement("Cafe_id");
    cafe_id_element.setAttribute("Cafe_id", QString::number(cafe_id));
    root.appendChild(cafe_id_element);

    QByteArray message_byte_array = message_document.toByteArray();

    size_t message_size = message_byte_array.size();
    message_byte_array.prepend(QString::number(message_size).toUtf8() + "\n");

    qDebug() << message_byte_array;

    socket->write(message_byte_array);

}

void Client::onReadyRead() {

    qDebug() << "On ready read called!";

    if (temporary_message->GetSize() == 0) {


        QByteArray size_byte_array = socket->readLine();
        size_byte_array.removeLast();
        size_t message_size = size_byte_array.toInt();


        if (socket->bytesAvailable() != 0) {

            QByteArray message_byte_array = socket->read(socket->bytesAvailable());

            temporary_message = std::make_shared<Message>(message_size, message_byte_array);

            if (temporary_message->IsReady()) {

                incoming_messages.push_front(std::move(temporary_message));

                temporary_message = std::make_shared<Message>();

            }

        }

    } else {

        if (temporary_message->IsReady()) {

            incoming_messages.push_front(std::move(temporary_message));

            temporary_message = std::make_shared<Message>();

        } else {

            QByteArray new_array = socket->read(socket->bytesAvailable());

            temporary_message->AppendToMessageByteArray(new_array);

            if (temporary_message->IsReady()) {

                incoming_messages.push_front(std::move(temporary_message));

                temporary_message = std::make_shared<Message>();

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

    QDomDocument message_document;
    message_document.setContent(message_byte_array);

    QDomElement root = message_document.firstChildElement();
    QDomNodeList children_nodes = root.childNodes();

    QString theme = children_nodes.at(0).toElement().attribute("Theme");

    if (theme == "Login") {

        QString result = children_nodes.at(1).toElement().attribute("Result");

        if (result == "Login_accepted") {

            QString nickname_data = children_nodes.at(2).toElement().attribute("Nickname");
            nickname = nickname_data;

            emit loggedIn();

        } else if (result == "Login_error") {

            QString error_description = children_nodes.at(2).toElement().attribute("Error_description");

            emit showMessage("Ошибка авторизации", error_description);

        }


    } else if (theme == "Register") {

        QString result = children_nodes.at(1).toElement().attribute("Result");
        qDebug() << result;

        if (result == "Register_accepted") {

            emit showMessage("Регистрация", "Регистрация прошла успешно!");
            emit registered();

        } else if (result == "Register_error") {

            QString error_description = children_nodes.at(2).toElement().attribute("Error_description");

            emit showMessage("Ошибка регистрации", error_description);

        }


    } else if (theme == "Cafe_objects") {

        QString result = children_nodes.at(1).toElement().attribute("Result");

        if (result == "Success") {

            QDomNodeList cafe_list = children_nodes.at(2).childNodes();

            for (int i = 0; i < cafe_list.count(); ++i) {

                int cafe_id = cafe_list.at(i).toElement().attribute("Id").toInt();
                QString name = cafe_list.at(i).toElement().attribute("Name");
                QString city = cafe_list.at(i).toElement().attribute("City");
                QString street = cafe_list.at(i).toElement().attribute("Street");
                int house_number = cafe_list.at(i).toElement().attribute("House_number").toInt();
                double latitude = cafe_list.at(i).toElement().attribute("Latitude").toDouble();
                double longitude = cafe_list.at(i).toElement().attribute("Longitude").toDouble();
                float average_rating = cafe_list.at(i).toElement().attribute("Average_rating").toFloat();

                emit addCafeObject(cafe_id, name, city, street, house_number, latitude, longitude, average_rating);

            }

        } else if (result == "Error") {

            QString error_description = children_nodes.at(2).toElement().attribute("Error_description");

            emit showMessage("Cafe objects error", error_description);

        }

    } else if (theme == "Cafe_reviews") {

        QString result = children_nodes.at(1).toElement().attribute("Result");

        if (result == "Success") {

            QDomNodeList reviews_list = children_nodes.at(2).childNodes();

            for (int i = 0; i < reviews_list.count(); ++i) {

                QString reviewer = reviews_list.at(i).toElement().attribute("Reviewer");
                int cafe_id = reviews_list.at(i).toElement().attribute("Cafe_id").toInt();
                int star_rating = reviews_list.at(i).toElement().attribute("Star_rating").toInt();
                QString review_text = reviews_list.at(i).toElement().attribute("Review_text");
                QString review_date = reviews_list.at(i).toElement().attribute("Review_date");

                emit addCafeReview(reviewer, cafe_id, star_rating, review_text, review_date);

            }

        } else if (result == "Error") {

            QString error_description = children_nodes.at(2).toElement().attribute("Error_description");

            emit showMessage("Cafe reviews error", error_description);

        }


    }

}





