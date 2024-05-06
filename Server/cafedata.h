#ifndef CAFEDATA_H
#define CAFEDATA_H

#include <QString>

class CafeData
{
public:
    CafeData(const QString& name, const QString& city, const QString& street,
             const QString& house_number, const QString& latitude, const QString& longitude);

    CafeData(const QString& name, const QString& city, const QString& street, const QString& house_number);

    QString GetName() const;
    QString GetCity() const;
    QString GetStreet() const;
    QString GetHouseNumber() const;
    QString GetLatitude() const;
    QString GetLongitude() const;

private:
    QString name;
    QString city;
    QString street;
    QString house_number;
    QString latitude;
    QString longitude;

};

#endif // CAFEDATA_H