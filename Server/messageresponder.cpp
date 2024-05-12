#include "messageresponder.h"


MessageResponder::MessageResponder(QObject* parent,
                                   const QByteArray& incoming_message,
                                   ThreadSafeList<Connection> &connections,
                                   std::atomic<unsigned long long>& sql_connections_counter) : QObject(parent),
                                                                                               incoming_message(incoming_message),
                                                                                               connections(connections),
                                                                                               sql_connections_counter(sql_connections_counter) {}

void MessageResponder::run() {

    qDebug() << "Respond to message started!";;

    QDomDocument document;
    document.setContent(incoming_message);

    QDomElement root = document.firstChildElement();
    QDomNodeList children_nodes = root.childNodes();

    QString action = children_nodes.at(0).toElement().attribute("Action");

    if (action == "Login") {

        QDomElement login_data = children_nodes.at(1).toElement();
        Login(login_data.attribute("Nickname"), login_data.attribute("Password"));

    } else if (action == "Register") {

        QDomElement register_data = children_nodes.at(1).toElement();
        Register(register_data.attribute("Nickname"), register_data.attribute("Password"));

    }

}

void MessageResponder::Login(const QString &nickname, const QString &password) {

    qDebug() << "Login function start!";

    LoginResult login_result = sql_service->Login(nickname, password);

    qDebug() << "log 1";

    QDomDocument message_document;
    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    if (login_result == LoginResult::SUCCESS) {


        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Login_accepted");
        root.appendChild(action);

        QDomElement nickname_element = message_document.createElement("Nickname");
        nickname_element.setAttribute("Nickname", nickname);
        root.appendChild(nickname_element);


    } else if (login_result == LoginResult::INCORRECT_PASSWORD) {


        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Login_error");
        root.appendChild(action);

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Incorrect password");
        root.appendChild(error_description);


    } else if (login_result == LoginResult::NO_USER_IN_DATABASE) {


        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Login_error");

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Unregistered nickname");
        root.appendChild(error_description);


    } else if (login_result == LoginResult::DATABASE_ERROR) {


        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Login_error");
        root.appendChild(action);

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Database error");
        root.appendChild(error_description);

    }

    QByteArray message_byte_array = message_document.toByteArray();

    size_t message_size = message_byte_array.size();
    message_byte_array.prepend(QString::number(message_size).toUtf8() + "\n");

    emit MessageResponceReady(message_byte_array);

}

void MessageResponder::Register(const QString &nickname, const QString &password) {

    RegisterResult register_result = sql_service->Register(nickname, password);

    QDomDocument message_document;
    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    if (register_result == RegisterResult::SUCCESS) {


        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Register_accepted");
        root.appendChild(action);


    } else if (register_result == RegisterResult::NICKNAME_IS_ALREADY_IN_USE) {


        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Register_error");
        root.appendChild(action);

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Nikcname is already registered");
        root.appendChild(error_description);


    } else if (register_result == RegisterResult::DATABASE_ERROR) {


        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Register_error");
        root.appendChild(action);

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Database error");
        root.appendChild(error_description);


    }

    QByteArray message_byte_array = message_document.toByteArray();

    size_t message_size = message_byte_array.size();
    message_byte_array.prepend(QString::number(message_size).toUtf8() + "\n");

    emit MessageResponceReady(message_byte_array);

}
