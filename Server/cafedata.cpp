#include "cafedata.h"

CafeData::CafeData(const int &cafe_id,
                   const QString &name,
                   const QString &city,
                   const QString &street,
                   const QString &house_number,
                   const QString &latitude,
                   const QString &longitude,
                   const QString& average_rating) : cafe_id(cafe_id), name(name), city(city),
                                                    street(street), house_number(house_number), latitude(latitude),
                                                    longitude(longitude), average_rating(average_rating) {}

CafeData::CafeData(const QString &name, const QString &city,
                   const QString &street, const QString &house_number,
                   const QString &latitude, const QString &longitude) : cafe_id(0), average_rating(""), name(name), city(city),
                                                                        street(street), house_number(house_number),
                                                                        latitude(latitude), longitude(longitude) {}

CafeData::CafeData(const QString &name, const QString &city,
                   const QString &street, const QString &house_number) : cafe_id(0), average_rating(""), name(name),
                                                                         city(city), street(street), house_number(house_number) {}

bool CafeData::operator ==(const CafeData &other) {

    return (average_rating == other.average_rating && cafe_id == other.cafe_id && name == other.name &&
            city == other.city && street == other.street && house_number == other.house_number &&
            latitude == other.latitude && longitude == other.longitude);

}

int CafeData::GetId() const {

    return cafe_id;

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

QString CafeData::GetAverageRating() const {

    return average_rating;

}
