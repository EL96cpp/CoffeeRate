import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning


MapQuickItem {

    id: user_map_marker 

    anchorPoint.x: user_marker_image.width/2
    anchorPoint.y: user_marker_image.height
    coordinate: QtPositioning.coordinate(map.center.latitude, map.center.longitude)

    Drag.active: dragArea.drag.active

    signal setUserMarkerPosition;

    sourceItem: Image {

        id: user_marker_image

        source: "qrc:/Images/user_mark.png"

    }

    MouseArea {

        id: dragArea
        anchors.fill: parent
        drag.target: parent
        propagateComposedEvents: true
        onReleased: {

            user_map_marker.Drag.drop();

        }

    }


}
