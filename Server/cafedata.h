#ifndef CAFEDATA_H
#define CAFEDATA_H

#include <QString>
#include <QDebug>

class CafeData
{
public:
    CafeData(const int& cafe_id, const QString& name, const QString& city, const QString& street,
             const QString& house_number, const QString& latitude, const QString& longitude, const QString& average_rating);

    CafeData(const QString& name, const QString& city, const QString& street,
             const QString& house_number, const QString& latitude, const QString& longitude);

    CafeData(const QString& name, const QString& city, const QString& street, const QString& house_number);

    bool operator == (const CafeData& other);

    int GetId() const;
    QString GetName() const;
    QString GetCity() const;
    QString GetStreet() const;
    QString GetHouseNumber() const;
    QString GetLatitude() const;
    QString GetLongitude() const;
    QString GetAverageRating() const;

private:
    int cafe_id;
    QString name;
    QString city;
    QString street;
    QString house_number;
    QString latitude;
    QString longitude;
    QString average_rating;

};


#endif // CAFEDATA_H
