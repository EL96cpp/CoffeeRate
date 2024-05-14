#include "messageresponder.h"


MessageResponder::MessageResponder(QObject* parent,
                                   const QByteArray& incoming_message,
                                   ThreadSafeList<Connection> &connections,
                                   std::atomic<unsigned long long>& sql_connections_counter) : QObject(parent),
                                                                                               incoming_message(incoming_message),
                                                                                               connections(connections),
                                                                                               sql_connections_counter(sql_connections_counter) {

    sql_service = new SqlService(this, QString::number(sql_connections_counter));

}

void MessageResponder::run() {

    qDebug() << "Respond to message started!";

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

    } else if (action == "Get reviews") {

        QDomElement cafe_id_element = children_nodes.at(1).toElement();
        SendCafeReviews(cafe_id_element.attribute("Cafe_id").toUtf8().toInt());

    }

}

void MessageResponder::Login(const QString &nickname, const QString &password) {


    LoginResult login_result = sql_service->Login(nickname, password);

    QDomDocument message_document;
    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    if (login_result == LoginResult::SUCCESS) {


        qDebug() << "Success";

        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Login_accepted");
        root.appendChild(action);

        QDomElement nickname_element = message_document.createElement("Nickname");
        nickname_element.setAttribute("Nickname", nickname);
        root.appendChild(nickname_element);


    } else if (login_result == LoginResult::INCORRECT_PASSWORD) {


        qDebug() << "Incorrect password";

        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Login_error");
        root.appendChild(action);

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Incorrect password");
        root.appendChild(error_description);


    } else if (login_result == LoginResult::NO_USER_IN_DATABASE) {


        qDebug() << "No user in database";

        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Login_error");

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Unregistered nickname");
        root.appendChild(error_description);


    } else if (login_result == LoginResult::DATABASE_ERROR) {


        qDebug() << "Database error";

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

    qDebug() << "Will send message signal!";
    qDebug() << message_byte_array;

    emit MessageResponceIsReady(message_byte_array);

    if (login_result == LoginResult::SUCCESS) {

        SendAllCafeObjects();

    }


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

    qDebug() << "Will send message signal!";
    qDebug() << message_byte_array;

    emit MessageResponceIsReady(message_byte_array);

}

void MessageResponder::SendCafeReviews(const int &cafe_id) {

    QPair<GetCafeReviewsResult, QVector<CafeReview>> result = sql_service->GetCafeReviews(cafe_id);

    QDomDocument message_document;

    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    if (result.first == GetCafeReviewsResult::SUCCESS) {

        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Set cafe reviews");
        root.appendChild(action);

        QDomElement review_objects = message_document.createElement("Cafe reviews");
        root.appendChild(review_objects);

        for (auto& cafe_review : result.second) {

            QDomElement review_data = message_document.createElement("Review data");

            review_data.setAttribute("Reviewer", cafe_review.GetReviewerNickname());
            review_data.setAttribute("Cafe_id", cafe_review.GetCafeId());
            review_data.setAttribute("Star_rating", cafe_review.GetStarRating());
            review_data.setAttribute("Review_text", cafe_review.GetReviewText());
            review_data.setAttribute("Review_date", cafe_review.GetReviewDate());

            review_objects.appendChild(review_data);

        }

    } else if (result.first == GetCafeReviewsResult::NO_CAFE_IN_DATABASE) {

        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Cafe reviews error");
        root.appendChild(action);

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Unkonw cafe id");
        root.appendChild(error_description);

    } else if (result.first == GetCafeReviewsResult::DATABASE_ERROR) {

        QDomElement action = message_document.createElement("Action");
        action.setAttribute("Action", "Cafe reviews error");
        root.appendChild(action);

        QDomElement error_description = message_document.createElement("Error_description");
        error_description.setAttribute("Error_description", "Database error");
        root.appendChild(error_description);

    }

    QByteArray message_byte_array = message_document.toByteArray();

    size_t message_size = message_byte_array.size();
    message_byte_array.prepend(QString::number(message_size).toUtf8() + "\n");

    emit MessageResponceIsReady(message_byte_array);

}

void MessageResponder::SendAllCafeObjects() {

    QVector<CafeData> cafe_data = sql_service->GetAllCafeData();

    QDomDocument message_document;

    QDomElement root = message_document.createElement("Message");
    message_document.appendChild(root);

    QDomElement action = message_document.createElement("Action");
    action.setAttribute("Action", "Set cafe objects");
    root.appendChild(action);

    QDomElement cafe_objects = message_document.createElement("Cafe data");
    root.appendChild(cafe_objects);

    for (auto& data : cafe_data) {

        QDomElement data_element = message_document.createElement("Cafe data");

        data_element.setAttribute("Id", data.GetId());
        data_element.setAttribute("Name", data.GetName());
        data_element.setAttribute("City", data.GetCity());
        data_element.setAttribute("Street", data.GetStreet());
        data_element.setAttribute("House number", data.GetHouseNumber());
        data_element.setAttribute("Average rating", data.GetAverageRating());

        cafe_objects.appendChild(data_element);

    }

    QByteArray message_byte_array = message_document.toByteArray();

    size_t message_size = message_byte_array.size();
    message_byte_array.prepend(QString::number(message_size).toUtf8() + "\n");

    qDebug() << "Send message responce ready for cafe objects data!";

    emit MessageResponceIsReady(message_byte_array);

}
