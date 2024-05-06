#include "sqlservice.h"

SqlService::SqlService(QObject *parent)
    : QObject{parent}
{}

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

AddCafeReviewResult SqlService::AddCafeReview(const CafeData& cafe_data, const QString& nickname, const QString &star_rating, const QString &review_text) {

    CheckResult check_nickname_result = CheckIfNicknameExists(nickname);
    CheckResult check_cafe_result = CheckIfCafeRegistered(cafe_data);

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

CheckResult SqlService::CheckIfCafeRegistered(const CafeData& cafe_data) {

    QSqlQuery check_cafe_query(sql_database);
    check_cafe_query.prepare("SELECT EXISTS (SELECT 1 FROM cafes WHERE name_of_cafe = (?), city = (?), street = (?), house_number = (?),"
                             "latitude = (?), longitude = (?))");
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
    check_nickname_query.prepare("SELECT EXISTS (SELECT 1 FROM customers WHERE nickname = (?))");
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

bool SqlService::CheckIfStarRatingCorrect(const QString &star_rating) {

    return (star_rating.toInt() >= 1 && star_rating.toInt() <= 5);

}
