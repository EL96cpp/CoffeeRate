#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtXml>
#include <QDebug>
#include <thread>

#include "message.h"
#include "threadsafelist.h"

class Client : public QObject {

    Q_OBJECT
public:
    Client(QObject *parent = nullptr);

    void ConnectToServer(const QString& address, const quint16& port);

signals:
    void loggedIn();
    void registered();
    void cafeReviewAdded();
    void showMessage(const QString& error_title, const QString& error_description);
    void addCafeObject(const int& cafe_id, const QString& name, const QString& city, const QString& street,
                       const QString& house_number, const QString& latitude, const QString& longitude, const float& average_rating);
    void addCafeReview(const QString& reviewer, const int& cafe_id, const int& star_rating,
                       const QString& review_text, const QString& review_date);
    void getCafeReviewsSuccess();

public slots:
    void onLogin(const QString& nickname, const QString& password);
    void onRegister(const QString& nickname, const QString& password);
    void onSendReview(const int& cafe_id, const QString& cafe_name, const QString& city, const QString& street, const QString& house_number,
                      const QString& latitude, const QString& longitude, const int& star_rating, const QString& review_text);
    void onGetCafeReviews(const int& cafe_id);
    void onReadyRead();

private:
    void ProcessMessages();
    void RespondToMessage(const QByteArray& message_byte_array);

private:
    QTcpSocket* socket;
    QString nickname;
    std::thread message_processing_thread;
    std::shared_ptr<Message> temporary_message;
    ThreadSafeList<Message> incoming_messages;

};

#endif // CLIENT_H
