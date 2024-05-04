#ifndef SQLSERVICE_H
#define SQLSERVICE_H

#include <QObject>

class SqlService : public QObject
{
    Q_OBJECT
public:
    explicit SqlService(QObject *parent = nullptr);

signals:
};

#endif // SQLSERVICE_H
