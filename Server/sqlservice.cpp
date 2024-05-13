#include "sqlservice.h"

SqlService::SqlService(QObject *parent, const QString &sql_connestions_counter) :
                      QObject(parent), sql_database(QSqlDatabase::addDatabase("QPSQL", sql_connestions_counter)) {


    sql_database.setHostName("127.0.0.1");
    sql_database.setPort(5432);
    sql_database.setDatabaseName("coffee_rate");
    sql_database.setUserName("postgres");
    sql_database.setPassword("postgres");
    bool started = sql_database.open();

}

LoginResult SqlService::Login(const QString &nickname, const QString &password) {

    CheckResult check_nickname_result = CheckIfNicknameExists(nickname);

    if (check_nickname_result == CheckResult::FALSE) {

        return LoginResult::NO_USER_IN_DATABASE;

    } else if (check_nickname_result == CheckResult::DATABASE_ERROR) {

        return LoginResult::DATABASE_ERROR;

    } else if (check_nickname_result == CheckResult::TRUE) {

        QSqlQuery get_password_query(sql_database);
        get_password_query.prepare("SELECT password FROM users WHERE nickname = (?)");
        get_password_query.addBindValue(nickname);

        if (get_password_query.exec()) {

            if (get_password_query.next()) {

                QString correct_password = get_password_query.value(0).toString();

                if (password == correct_password) {

                    return LoginResult::SUCCESS;

                } else {

                    return LoginResult::INCORRECT_PASSWORD;

                }

            } else {

                return LoginResult::DATABASE_ERROR;

            }

        } else {

            return LoginResult::DATABASE_ERROR;

        }

    }

}

RegisterResult SqlService::Register(const QString &nickname, const QString &password) {

    CheckResult check_nickname_result = CheckIfNicknameExists(nickname);

    if (check_nickname_result == CheckResult::TRUE) {

        return RegisterResult::NICKNAME_IS_ALREADY_IN_USE;

    } else if (check_nickname_result == CheckResult::DATABASE_ERROR) {

        return RegisterResult::DATABASE_ERROR;

    } else if (check_nickname_result == CheckResult::FALSE) {

        QSqlQuery register_user_query(sql_database);
        register_user_query.prepare("INSERT INTO users (nickname, password ) VALUES ((?), (?))");
        register_user_query.addBindValue(nickname);
        register_user_query.addBindValue(password);

        if (register_user_query.exec()) {

            return RegisterResult::SUCCESS;

        } else {

            return RegisterResult::DATABASE_ERROR;

        }

    }

}

AddCafeResult SqlService::AddNewCafe(const CafeData& cafe_data) {

    CheckResult check_cafe_result = CheckIfCafeRegistered(cafe_data);

    if (check_cafe_result == CheckResult::TRUE) {

        return AddCafeResult::CAFE_IS_ALREADY_REGISTERED;

    } else if (check_cafe_result == CheckResult::DATABASE_ERROR) {

        return AddCafeResult::DATABASE_ERROR;

    } else if (check_cafe_result == CheckResult::FALSE) {

        QSqlQuery add_cafe_query(sql_database);
        add_cafe_query.prepare("INSERT INTO cafes (name_of_cafe, city, street, house_number, latitude, longitude) "
                               "VALUES ((?), (?), (?), (?), (?), (?))");
        add_cafe_query.addBindValue(cafe_data.GetName());
        add_cafe_query.addBindValue(cafe_data.GetCity());
        add_cafe_query.addBindValue(cafe_data.GetStreet());
        add_cafe_query.addBindValue(cafe_data.GetHouseNumber());
        add_cafe_query.addBindValue(cafe_data.GetLatitude());
        add_cafe_query.addBindValue(cafe_data.GetLongitude());

        if (add_cafe_query.exec()) {

            return AddCafeResult::SUCCESS;

        } else {

            return AddCafeResult::DATABASE_ERROR;

        }

    }

}

AddCafeReviewResult SqlService::AddCafeReview(const CafeData& cafe_data, const int& cafe_id, const QString& nickname, const QString &star_rating, const QString &review_text) {

    CheckResult check_nickname_result = CheckIfNicknameExists(nickname);
    CheckResult check_cafe_result = CheckCafeIdIsCorrect(cafe_data, cafe_id);

    if (check_nickname_result == CheckResult::FALSE) {

        return AddCafeReviewResult::NO_USER_IN_DATABASE;

    } else if (check_nickname_result == CheckResult::DATABASE_ERROR) {

        return AddCafeReviewResult::DATABASE_ERROR;

    } else if (check_cafe_result == CheckResult::FALSE) {

        return AddCafeReviewResult::NO_CAFE_IN_DATABASE;

    } else if (check_cafe_result == CheckResult::DATABASE_ERROR) {

        return AddCafeReviewResult::DATABASE_ERROR;

    } else if (!CheckIfStarRatingCorrect(star_rating)) {

        return AddCafeReviewResult::INCORRECT_STAR_RATING;

    } else {

        QSqlQuery add_review_query(sql_database);
        add_review_query.prepare("INSERT INTO reviews (reviewer, name_of_cafe, city, street, house_number, star_rating, review_text) "
                                 "VALUES ((?), (?), (?), (?), (?), (?), ())");
        add_review_query.addBindValue(nickname);
        add_review_query.addBindValue(cafe_data.GetName());
        add_review_query.addBindValue(cafe_data.GetCity());
        add_review_query.addBindValue(cafe_data.GetStreet());
        add_review_query.addBindValue(cafe_data.GetHouseNumber());
        add_review_query.addBindValue(star_rating);
        add_review_query.addBindValue(review_text);

        if (add_review_query.exec()) {

            return AddCafeReviewResult::SUCCESS;

        } else {

            return AddCafeReviewResult::DATABASE_ERROR;

        }

    }

}

QVector<CafeData> SqlService::GetAllCafeData() {

    QSqlQuery get_data_query(sql_database);
    get_data_query.prepare("SELECT id, name_of_cafe, city, street, house_number, latitude, longitude, "
                           "(SELECT AVG(star_rating) FROM reviews WHERE cafe_id = id) FROM cafes");

    get_data_query.exec();

    QVector<CafeData> cafe_data;

    while (get_data_query.next()) {

        int cafe_id = get_data_query.value(0).toInt();
        QString cafe_name = get_data_query.value(1).toString();
        QString city = get_data_query.value(2).toString();
        QString street = get_data_query.value(3).toString();
        QString house_number = get_data_query.value(4).toString();
        QString latitude = get_data_query.value(5).toString();
        QString longitude = get_data_query.value(6).toString();
        QString average_rating = get_data_query.value(7).toString();

        average_rating = average_rating.left(3);

        cafe_data.emplace_back(cafe_id, cafe_name, city, street, house_number, latitude, longitude, average_rating);

    }

    return cafe_data;

}

CheckResult SqlService::CheckIfCafeRegistered(const CafeData& cafe_data) {

    QSqlQuery check_cafe_query(sql_database);
    check_cafe_query.prepare("SELECT EXISTS (SELECT 1 FROM cafes WHERE name_of_cafe = (?), city = (?), street = (?),"
                             "house_number = (?), latitude = (?), longitude = (?))");
    check_cafe_query.addBindValue(cafe_data.GetName());
    check_cafe_query.addBindValue(cafe_data.GetCity());
    check_cafe_query.addBindValue(cafe_data.GetStreet());
    check_cafe_query.addBindValue(cafe_data.GetHouseNumber());
    check_cafe_query.addBindValue(cafe_data.GetLatitude());
    check_cafe_query.addBindValue(cafe_data.GetLongitude());

    check_cafe_query.exec();

    if (check_cafe_query.next()) {

        if (check_cafe_query.value(0).toBool()) {

            return CheckResult::TRUE;

        } else {

            return CheckResult::FALSE;

        }

    } else {

        return CheckResult::DATABASE_ERROR;

    }

}

CheckResult SqlService::CheckIfNicknameExists(const QString &nickname) {

    QSqlQuery check_nickname_query(sql_database);
    check_nickname_query.prepare("SELECT EXISTS (SELECT 1 FROM users WHERE nickname = (?))");
    check_nickname_query.addBindValue(nickname);

    check_nickname_query.exec();

    if (check_nickname_query.next()) {

        if (check_nickname_query.value(0).toBool()) {

            return CheckResult::TRUE;

        } else {

            return CheckResult::FALSE;

        }

    } else {

        return CheckResult::DATABASE_ERROR;

    }

}

CheckResult SqlService::CheckCafeIdIsCorrect(const CafeData &cafe_data, const int &cafe_id) {

    QSqlQuery check_cafe_query(sql_database);
    check_cafe_query.prepare("SELECT name_of_cafe, city, street, house_number, latitude, longitude"
                             " FROM cafes WHERE id = (?)");
    check_cafe_query.addBindValue(cafe_id);

    check_cafe_query.exec();

    if (check_cafe_query.next()) {

        QString name_of_cafe = check_cafe_query.value(0).toString();
        QString city = check_cafe_query.value(1).toString();
        QString street = check_cafe_query.value(2).toString();
        QString house_number = check_cafe_query.value(3).toString();
        QString latitude = check_cafe_query.value(4).toString();
        QString longitude = check_cafe_query.value(5).toString();

        CafeData actual_data(name_of_cafe, city, street, house_number, latitude, longitude);

        if (actual_data == cafe_data) {

            return CheckResult::TRUE;

        } else {

            return CheckResult::FALSE;

        }

    } else {

        return CheckResult::DATABASE_ERROR;

    }

}

bool SqlService::CheckIfStarRatingCorrect(const QString &star_rating) {

    return (star_rating.toInt() >= 1 && star_rating.toInt() <= 5);

}
