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
        color: light_brown
        border.width: 1
        border.color: pale
        anchors.centerIn: parent

        Plugin {

            id: mapPlugin
            name: "osm"

        }

        Row {

            id: map_header_row
            width: parent.width*0.9
            height: parent.height*0.1

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1/2

            Rectangle {

                id: reviews_navigation_rectangle
                width: parent.width/3
                height: parent.height
                color: reviews_navigation_mouse_area.containsMouse ? orange : dark_brown

                Text {

                    id: reviews_navigation_text

                    text: "Отзывы"
                    font.pointSize: 15
                    color: reviews_navigation_mouse_area.containsMouse ? pale : yellow

                    anchors.centerIn: parent

                }

                MouseArea {

                    id: reviews_navigation_mouse_area

                    hoverEnabled: true
                    anchors.fill: parent

                    onClicked: {

                        map.state = "show_reviews"

                    }

                }

            }

            Rectangle {

                id: route_navigation_rectangle
                width: parent.width/3
                height: parent.height

                color: route_navigation_mouse_area.containsMouse ? orange : dark_brown

                Text {

                    id: route_navigation_text

                    text: "Проложить\nмаршрут"
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                    color: route_navigation_mouse_area.containsMouse ? pale : yellow

                    anchors.centerIn: parent

                }

                MouseArea {

                    id: route_navigation_mouse_area

                    hoverEnabled: true
                    anchors.fill: parent

                    onClicked: {

                        map.state = "build_route"
                        user_map_marker.coordinate = map.center

                    }

                }

            }

            Rectangle {

                id: add_cafe_navigation_rectangle
                width: parent.width/3
                height: parent.height

                color: add_cafe_navigation_mouse_area.containsMouse ? orange : dark_brown

                Text {

                    id: add_cafe_navigation_text
                    text: "Добавить\nкафе"
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                    color: add_cafe_navigation_mouse_area.containsMouse ? pale : yellow

                    anchors.centerIn: parent

                }

                MouseArea {

                    id: add_cafe_navigation_mouse_area

                    hoverEnabled: true
                    anchors.fill: parent

                    onClicked: {

                        map.state = "add_cafe"
                        user_map_marker.coordinate = map.center

                    }

                }

            }

        }

        Map {

            id: map
            width: parent.width*0.9
            height: parent.height*0.7
            plugin: mapPlugin
            center: QtPositioning.coordinate(55.755, 37.617)
            zoomLevel: 15
            minimumZoomLevel: 11
            maximumZoomLevel: 20

            states: [

                State {

                    name: "show_reviews"

                    PropertyChanges {
                        target: user_map_marker
                        visible: false
                    }

                },

                State {

                    name: "build_route"

                    PropertyChanges {
                        target: user_map_marker
                        visible: true
                    }

                },

                State {

                    name: "add_cafe"

                    PropertyChanges {
                        target: user_map_marker
                        visible: true
                    }

                }

            ]

            state: "show_reviews"

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: map_header_row.bottom

            property geoCoordinate startCentroid

            property string user_marker_latitude
            property string user_marker_longitude


            onZoomLevelChanged: {

                if (zoomLevel < minimumZoomLevel) {

                    zoomLevel = minimumZoomLevel

                } else if (zoomLevel > maximumZoomLevel) {

                    zoomLevel = maximumZoomLevel

                }

            }

            UserMapMarker {

                id: user_map_marker

                visible: false

            }

            RouteModel {

                id: route_model
                plugin: map.plugin
                autoUpdate: true

                query: RouteQuery {

                    id: route_query
                    routeOptimizations: RouteQuery.ShortestRoute

                }

            }

            MapItemView {

                id: route_view
                model: route_model
                delegate: Component {

                    MapRoute {

                        route: routeData
                        line.color: flamenco_orange
                        line.width: 4

                    }

                }

            }

            MapItemView {

                id: places_view

                model: cafe_objects_model

                delegate: marker_component

            }


            DropArea {

                id: dropAreaRed

                anchors.fill: parent

                onDropped: (drop) => {

                    var coord = map.toCoordinate(Qt.point(drop.x, drop.y));
                    console.log("latitude:" + coord.latitude + ", longitude:" + coord.longitude);
                    map.user_marker_latitude = coord.latitude;
                    map.user_marker_longitude = coord.longitude;

                    route_query.clearWaypoints();
                    route_model.reset();
                    route_query.addWaypoint(QtPositioning.coordinate(coord.latitude, coord.longitude));

                }

            }

        }

        Rectangle {

            id: lower_rectangle
            width: map_header_row.width
            height: parent.height*0.1
            color: dark_brown

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: map.bottom

            Item {

                id: build_route_elements

                width: parent.width
                height: parent.height

                property real distance

                visible: map.state === "build_route"

                Text {

                    id: route_length_title
                    text: "Длина маршрута:"
                    horizontalAlignment: Text.AlignLeft
                    font.pointSize: 14
                    color: pale
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 20

                }

                Text {

                    id: route_length_value
                    text: build_route_elements.distance
                    font.pointSize: 14
                    color: orange
                    anchors.left: route_length_title.right
                    anchors.verticalCenter: route_length_title.verticalCenter
                    anchors.rightMargin: 10

                }

                CustomButton {

                    id: rebuild_route_button
                    button_width: 150
                    button_height: 40

                    border_width: 0
                    button_radius: 20
                    button_text: "Новый маршрут"
                    text_color: light_sand
                    text_color_hovered: "white"
                    font_point_size: 12
                    rect_color: light_brown
                    rect_color_hovered: orange

                    anchors.verticalCenter: route_length_value.verticalCenter
                    anchors.right: parent.right
                    anchors.leftMargin: 20

                }

                Connections {

                    target: rebuild_route_button

                    function onButtonClickedSignal() {

                        route_query.clearWaypoints();
                        route_model.reset();

                    }

                }

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

                    Rectangle {

                        id: marker_description_rectangle
                        width: Math.max(cafe_name.paintedWidth, cafe_address.paintedWidth) + cafe_name.anchors.margins*2
                        height: cafe_name.paintedHeight + cafe_name.anchors.margins*4 + cafe_address.paintedHeight +
                                cafe_rating.paintedHeight
                        radius: 5
                        color: cafe_mark_background_color

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

                            if (map.state === "show_reviews") {

                                Client.onGetCafeReviews(model.cafe_id);

                                reviews_page.cafe_id = model.cafe_id;
                                reviews_page.cafe_name = model.name;
                                reviews_page.cafe_address = model.street + ", " + model.house_number;
                                reviews_page.cafe_rating = model.average_rating;

                                reviews_page.city = model.city;
                                reviews_page.street = model.street;
                                reviews_page.house_number = model.house_number;
                                reviews_page.latitude = model.latitude;
                                reviews_page.longitude = model.longitude;

                            } else if (map.state === "build_route") {

                                route_query.addWaypoint(QtPositioning.coordinate(model.latitude, model.longitude));
                                //build_route_elements.distance = route_query.get();

                            } else if (map.state === "add_cafe") {



                            }

                        }

                    }

                }

            }


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
