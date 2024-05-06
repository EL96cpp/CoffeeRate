#include "cafedata.h"

CafeData::CafeData(const QString &name, const QString &city,
                   const QString &street, const QString &house_number,
                   const QString &latitude, const QString &longitude) : name(name), city(city),
                                                                        street(street), house_number(house_number),
                                                                        latitude(latitude), longitude(longitude) {}

CafeData::CafeData(const QString &name, const QString &city,
                   const QString &street, const QString &house_number) : name(name), city(city),
                                                                         street(street), house_number(house_number) {}

QString CafeData::GetName() const {

    return name;

}

QString CafeData::GetCity() const {

    return city;

}

QString CafeData::GetStreet() const {

    return street;

}

QString CafeData::GetHouseNumber() const {

    return house_number;

}

QString CafeData::GetLatitude() const {

    return latitude;

}

QString CafeData::GetLongitude() const {

    return longitude;

}
