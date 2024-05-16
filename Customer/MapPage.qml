import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning

Page {

    id: map_page

    visible: false

    property string cafe_mark_background_color: dark_brown
    property string cafe_mark_text_color: yellow

    Image {

        id: background_image

        source: "qrc:/Images/background.jpg"

        anchors.fill: parent

    }

    Rectangle {

        id: map_rectangle
        width: main_window.width*0.95
        height: main_window.height*0.9
        radius: 10
        color: pale

        anchors.centerIn: parent

        Plugin {

            id: mapPlugin
            name: "osm"

        }

        Map {

            id: map
            width: parent.width*0.9
            height: parent.height*0.9
            anchors.centerIn: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(55.755, 37.617)
            zoomLevel: 15
            minimumZoomLevel: 11
            maximumZoomLevel: 20

            property geoCoordinate startCentroid

            onZoomLevelChanged: {

                if (zoomLevel < minimumZoomLevel) {

                    zoomLevel = minimumZoomLevel

                } else if (zoomLevel > maximumZoomLevel) {

                    zoomLevel = maximumZoomLevel

                }

            }


            MapItemView {

                id: places_view

                model: cafe_objects_model

                delegate: marker_component

            }



        }

        Component {

            id: marker_component

            MapQuickItem {

                id: marker
                anchorPoint.x: image.width/2
                anchorPoint.y: image.height

                coordinate: QtPositioning.coordinate(model.latitude, model.longitude)

                sourceItem: Image {

                    id: image

                    source: "qrc:/Images/cafe_mark.png"
                    z: 1

                    Rectangle {

                        id: marker_description_rectangle
                        width: Math.max(cafe_name.paintedWidth, cafe_address.paintedWidth) + cafe_name.anchors.margins*2
                        height: cafe_name.paintedHeight + cafe_name.anchors.margins*4 + cafe_address.paintedHeight +
                                cafe_rating.paintedHeight
                        radius: 5
                        color: cafe_mark_background_color

                        z: 10

                        anchors.left: parent.horizontalCenter
                        anchors.top: parent.bottom

                        visible: marker_mouse_area.containsMouse

                        Text {

                            id: cafe_name
                            text: model.name
                            font.pointSize: 14
                            font.bold: true
                            font.underline: true
                            color: cafe_mark_text_color

                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.margins: 5

                        }

                        Text {

                            id: cafe_address
                            text: model.street + ", " + model.house_number
                            font.pointSize: 10
                            color: cafe_mark_text_color

                            anchors.top: cafe_name.bottom
                            anchors.left: cafe_name.left
                            anchors.topMargin: 5

                        }

                        Text {

                            id: cafe_rating
                            text: model.average_rating
                            font.pointSize: 10
                            color: cafe_mark_text_color

                            anchors.right: rating_star.left
                            anchors.verticalCenter: rating_star.verticalCenter
                            anchors.rightMargin: 5

                        }

                        Star {

                            id: rating_star

                            star_width: cafe_rating.paintedHeight
                            star_color: cafe_mark_text_color

                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: 5

                        }

                    }

                    MouseArea {

                        id: marker_mouse_area

                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {

                            Client.onGetCafeReviews(model.cafe_id);

                        }

                    }

                }

            }


        }

        Address {

            id: address_example
            city: "Moscow"
            country: "Russia"
            street: "New Arbat Avenue"

        }

        PinchHandler {

            id: pinch
            target: null
            onActiveChanged: if (active) {
                map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
            }
            onScaleChanged: (delta) => {
                map.zoomLevel += Math.log2(delta)
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
            onRotationChanged: (delta) => {
                map.bearing -= delta
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
            grabPermissions: PointerHandler.TakeOverForbidden

        }


        WheelHandler {

            id: wheel
            target: map
            acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
            orientation: Qt.Vertical
            rotationScale: 1/120
            property: "zoomLevel"

        }

        DragHandler {

            id: drag
            target: null

            property var upper_left
            property var lower_left
            property var upper_right
            property var lower_right

            onTranslationChanged: (delta) => {

                map.pan(-delta.x, -delta.y);

            }

        }

    }


    ListModel {

        id: cafe_objects_model

    }


    Connections {

        target: Client

        function onAddCafeObject(cafe_id, name, city, street, house_number, latitude, longitude, average_rating) {

            cafe_objects_model.append({ cafe_id: cafe_id, name: name, city: city, street:street, house_number: house_number,
                                        latitude: latitude, longitude: longitude, average_rating: average_rating });

        }

    }

    Connections {

        target: Client

        function onGetCafeReviewsSuccess() {

            stack_view.push(reviews_page);

        }

    }


}
