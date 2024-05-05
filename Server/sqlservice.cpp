#include "sqlservice.h"

SqlService::SqlService(QObject *parent)
    : QObject{parent}
{}

LoginResult SqlService::Login(const QString &nickname, const QString &password) {

    if (!CheckIfNicknameExists(nickname)) {

        return LoginResult::NO_USER_IN_DATABASE;

    } else {

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

    if (CheckIfNicknameExists(nickname)) {

        return RegisterResult::NICKNAME_IS_ALREADY_IN_USE;

    } else {

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

AddCafeReviewResult SqlService::AddCafeReview(const QString &nickname, const QString &name_of_cafe, const QString &city, const QString &street,
                                              const QString &house_number, const QString &star_rating, const QString &review_text) {

    if (!CheckIfNicknameExists(nickname)) {

        return AddCafeReviewResult::NO_USER_IN_DATABASE;

    } else if (!CheckIfCafeRegistered(name_of_cafe, city, street, house_number)) {

        return AddCafeReviewResult::NO_CAFE_IN_DATABASE;

    } else if (!CheckIfStarRatingCorrect(star_rating)) {

        return AddCafeReviewResult::INCORRECT_STAR_RATING;

    } else {

        QSqlQuery add_review_query(sql_database);
        add_review_query.prepare("INSERT INTO reviews (reviewer, name_of_cafe, city, street, house_number, star_rating, review_text) "
                                 "VALUES ((?), (?), (?), (?), (?), (?), ())");
        add_review_query.addBindValue(nickname);
        add_review_query.addBindValue(name_of_cafe);
        add_review_query.addBindValue(city);
        add_review_query.addBindValue(street);
        add_review_query.addBindValue(house_number);
        add_review_query.addBindValue(star_rating);
        add_review_query.addBindValue(review_text);

        if (add_review_query.exec()) {

            return AddCafeReviewResult::SUCCESS;

        } else {

            return AddCafeReviewResult::DATABASE_ERROR;

        }

    }

}

bool SqlService::CheckIfCafeRegistered(const QString &name_of_cafe, const QString &city, const QString &street, const QString &house_number) {

    QSqlQuery check_cafe_query(sql_database);
    check_cafe_query.prepare("SELECT EXISTS (SELECT 1 FROM cafes WHERE name_of_cafe = (?), city = (?), street = (?), house_number = (?))");
    check_cafe_query.addBindValue(name_of_cafe);
    check_cafe_query.addBindValue(city);
    check_cafe_query.addBindValue(street);
    check_cafe_query.addBindValue(house_number);

    check_cafe_query.exec();

    if (check_cafe_query.next()) {

        return check_cafe_query.value(0).toBool();

    }

}

bool SqlService::CheckIfNicknameExists(const QString &nickname) {

    QSqlQuery check_nickname_query(sql_database);
    check_nickname_query.prepare("SELECT EXISTS (SELECT 1 FROM customers WHERE nickname = (?))");
    check_nickname_query.addBindValue(nickname);

    check_nickname_query.exec();

    if (check_nickname_query.next()) {

        return check_nickname_query.value(0).toBool();

    }

}

bool SqlService::CheckIfStarRatingCorrect(const QString &star_rating) {

    return (star_rating.toInt() >= 1 && star_rating.toInt() <= 5);

}
