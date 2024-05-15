import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning

Page {

    id: map_page

    visible: false


    Image {

        id: background_image

        source: "qrc:/Images/background.jpg"

        anchors.fill: parent

    }


    ListModel {

        id: cafe_objects_model

    }

    Connections {

        target: Client

        function onAddCafeObject(cafe_id, name, city, street, house_number, latitude, longitude, average_rating) {

            cafe_objects_model.append({ cafe_id: cafe_id, name: name, city: city, street:street, house_number: house_number,
                                        latitude: latitude, longitude: longitude, average_rating: average_rating });

            console.log(cafe_id + " " + name + " " + city + " " + street + " " + house_number);

        }

    }

}
