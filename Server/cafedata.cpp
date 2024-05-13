#include "cafedata.h"

CafeData::CafeData(const int &cafe_id, const QString &name,
                   const QString &city, const QString &street,
                   const QString &house_number, const QString &latitude,
                   const QString &longitude) : cafe_id(cafe_id), name(name), city(city), street(street),
                                               house_number(house_number), latitude(latitude), longitude(longitude) {}

CafeData::CafeData(const QString &name, const QString &city,
                   const QString &street, const QString &house_number,
                   const QString &latitude, const QString &longitude) : cafe_id(0), name(name), city(city),
                                                                        street(street), house_number(house_number),
                                                                        latitude(latitude), longitude(longitude) {}

CafeData::CafeData(const QString &name, const QString &city,
                   const QString &street, const QString &house_number) : cafe_id(0), name(name), city(city),
                                                                         street(street), house_number(house_number) {}

bool CafeData::operator ==(const CafeData &other) {

    return (cafe_id == other.cafe_id && name == other.name && city == other.city && street == other.street &&
            house_number == other.house_number && latitude == other.latitude && longitude == other.longitude);

}

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
