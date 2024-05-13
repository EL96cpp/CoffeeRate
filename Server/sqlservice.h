#ifndef SQLSERVICE_H
#define SQLSERVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVector>

#include "cafedata.h"

enum class LoginResult {

    SUCCESS,
    NO_USER_IN_DATABASE,
    INCORRECT_PASSWORD,
    DATABASE_ERROR

};

enum class RegisterResult {

    SUCCESS,
    NICKNAME_IS_ALREADY_IN_USE,
    DATABASE_ERROR

};

enum class AddCafeResult {

    SUCCESS,
    CAFE_IS_ALREADY_REGISTERED,
    DATABASE_ERROR

};

enum class AddCafeReviewResult {

    SUCCESS,
    NO_CAFE_IN_DATABASE,
    NO_USER_IN_DATABASE,
    INCORRECT_STAR_RATING,
    DATABASE_ERROR

};

enum class CheckResult {

    TRUE,
    FALSE,
    DATABASE_ERROR

};


class SqlService : public QObject {

    Q_OBJECT
public:
    SqlService(QObject *parent, const QString& sql_connestions_counter);

    SqlService(const SqlService& other) = delete;
    SqlService& operator = (const SqlService& other) = delete;

    LoginResult Login(const QString& nickname, const QString& password);
    RegisterResult Register(const QString& nickname, const QString& password);
    AddCafeResult AddNewCafe(const CafeData& cafe_data);
    AddCafeReviewResult AddCafeReview(const CafeData& cafe_data, const int& cafe_id, const QString& nickname, const QString& star_rating, const QString& review_text);

    QVector<CafeData> GetAllCafeData();

signals:


private:
    CheckResult CheckIfNicknameExists(const QString& nickname);
    CheckResult CheckCafeIdIsCorrect(const CafeData& cafe_data, const int& cafe_id);
    CheckResult CheckIfCafeRegistered(const CafeData& cafe_data);
    bool CheckIfStarRatingCorrect(const QString& star_rating);

private:
    QSqlDatabase sql_database;

};

#endif // SQLSERVICE_H
