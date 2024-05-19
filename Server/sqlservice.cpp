#include "sqlservice.h"

SqlService::SqlService(QObject *parent, const QString &sql_connestions_counter) :
                      QObject(parent), sql_database(QSqlDatabase::addDatabase("QPSQL", sql_connestions_counter)) {


    sql_database.setHostName("127.0.0.1");
    sql_database.setPort(5432);
    sql_database.setDatabaseName("coffee_rate");
    sql_database.setUserName("postgres");
    sql_database.setPassword("postgres");
    sql_database.open();

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

AddCafeReviewResult SqlService::AddCafeReview(const CafeData& cafe_data, const int& cafe_id, const QString& nickname,
                                              const QString &star_rating, const QString &review_text, const QString& review_date) {

    CheckResult check_nickname_result = CheckIfNicknameExists(nickname);
    CheckResult check_cafe_result = CheckCafeIdIsCorrect(cafe_data, cafe_id);
    CheckResult check_time_limit = CheckIfReviewAllowed(nickname, cafe_id, review_date);

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

    } else if (check_time_limit == CheckResult::FALSE) {

        return AddCafeReviewResult::THIRTY_DAYS_HAVE_NOT_PASSED;

    } else if (check_time_limit == CheckResult::DATABASE_ERROR) {

        return AddCafeReviewResult::DATABASE_ERROR;

    } else {

        QSqlQuery add_review_query(sql_database);
        add_review_query.prepare("INSERT INTO reviews (reviewer, cafe_id, star_rating, review_text, review_date) "
                                 "VALUES ((?), (?), (?), (?), (?))");
        add_review_query.addBindValue(nickname);
        add_review_query.addBindValue(cafe_id);
        add_review_query.addBindValue(star_rating);
        add_review_query.addBindValue(review_text);
        add_review_query.addBindValue(review_date);

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

QPair<GetCafeReviewsResult, QVector<CafeReview>> SqlService::GetCafeReviews(const int &cafe_id) {

    CheckResult check_cafe_exists = CheckIfCafeExists(cafe_id);

    QVector<CafeReview> cafe_reviews;

    if (check_cafe_exists == CheckResult::TRUE) {

        QSqlQuery get_reviews_query(sql_database);
        get_reviews_query.prepare("SELECT reviewer, cafe_id, star_rating, review_text, review_date "
                                  "FROM reviews WHERE cafe_id = (?)");
        get_reviews_query.addBindValue(cafe_id);

        if (get_reviews_query.exec()) {

            while (get_reviews_query.next()) {

                QString reviewer_nickname = get_reviews_query.value(0).toString();
                QString cafe_id = get_reviews_query.value(1).toString();
                QString star_rating = get_reviews_query.value(2).toString();
                QString review_text = get_reviews_query.value(3).toString();
                QString review_date = get_reviews_query.value(4).toString();

                cafe_reviews.emplace_back(reviewer_nickname, cafe_id, star_rating, review_text, review_date);

            }

            return qMakePair(GetCafeReviewsResult::SUCCESS, cafe_reviews);

        } else {

            return qMakePair(GetCafeReviewsResult::DATABASE_ERROR, cafe_reviews);

        }


    } else if (check_cafe_exists == CheckResult::FALSE) {

        return qMakePair(GetCafeReviewsResult::NO_CAFE_IN_DATABASE, cafe_reviews);

    } else if (check_cafe_exists == CheckResult::DATABASE_ERROR) {

        return qMakePair(GetCafeReviewsResult::DATABASE_ERROR, cafe_reviews);

    }

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

CheckResult SqlService::CheckIfReviewAllowed(const QString &nickname, const int &cafe_id, const QString &review_date) {

    QSqlQuery check_review_exists_query(sql_database);
    check_review_exists_query.prepare("SELECT EXISTS (SELECT 1 FROM reviews WHERE reviewer = (?) AND cafe_id = (?))");
    check_review_exists_query.addBindValue(nickname);
    check_review_exists_query.addBindValue(cafe_id);

    bool review_exists;

    if (check_review_exists_query.exec()) {

        if (check_review_exists_query.next()) {

            review_exists = check_review_exists_query.value(0).toBool();

            if (!review_exists) {

                return CheckResult::TRUE;

            }

        } else {

            return CheckResult::DATABASE_ERROR;

        }

    } else {

        return CheckResult::DATABASE_ERROR;

    }

    if (review_exists) {

        QSqlQuery check_date_query(sql_database);
        check_date_query.prepare("SELECT review_date FROM reviews WHERE reviewer = (?) AND cafe_id = (?)"
                                 " ORDER BY review_date DESC LIMIT 1");
        check_date_query.addBindValue(nickname);
        check_date_query.addBindValue(cafe_id);

        if (check_date_query.exec()) {

            QDate last_review_date = check_date_query.value(0).toDate();

            QDate current_review_date = QDate::fromString(review_date);

            if (last_review_date.daysTo(current_review_date) < 30) {

                return CheckResult::FALSE;

            } else {

                return CheckResult::TRUE;

            }

        } else {

            return CheckResult::DATABASE_ERROR;

        }

    } else {

        return CheckResult::TRUE;

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

        qDebug() << "Sql database geo-data " << latitude << " " << longitude;

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

CheckResult SqlService::CheckIfCafeExists(const int &cafe_id) {

    QSqlQuery check_cafe_query(sql_database);
    check_cafe_query.prepare("SELECT EXISTS (SELECT 1 FROM cafes WHERE id = (?))");
    check_cafe_query.addBindValue(cafe_id);

    if (check_cafe_query.exec()) {

        if (check_cafe_query.next()) {

            if (check_cafe_query.value(0).toBool() == true) {

                return CheckResult::TRUE;

            } else {

                return CheckResult::FALSE;

            }

        } else {

            return CheckResult::DATABASE_ERROR;

        }

    } else {

        return CheckResult::DATABASE_ERROR;

    }

}

bool SqlService::CheckIfStarRatingCorrect(const QString &star_rating) {

    return (star_rating.toInt() >= 0 && star_rating.toInt() <= 5);

}
