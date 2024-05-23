import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning


MapQuickItem {

    id: user_map_marker 

    coordinate: QtPositioning.coordinate(map.center.latitude, map.center.longitude)

    z: dragArea.drag.active || dragArea.pressed ? 2 : 1

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 20
    Drag.hotSpot.y: 20


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
