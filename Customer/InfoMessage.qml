import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning


Item {

    id: info_message
    width: main_window.width/1.5
    height: width/2

    visible: false

    anchors.centerIn: parent

    property string info_message_title
    property string info_message_text

    Rectangle {

        id: info_message_header_rect
        width: parent.width
        height: parent.height/4
        color: orange

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        Text {

            id: message_title
            text: info_message.info_message_title
            color: pale
            font.pointSize: 20

            anchors.centerIn: parent

        }

    }

    Rectangle {

        id: info_message_body_rect
        width: parent.width
        height: parent.height - info_message_header_rect.height
        color: light_sand

        anchors.top: info_message_header_rect.bottom
        anchors.horizontalCenter: info_message_header_rect.horizontalCenter

        Text {

            id: message_text
            width: parent.width/1.1
            height: parent.height/1.1
            text: info_message.info_message_text
            color: "black"
            font.pointSize: 20
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: font.pixelSize/2

        }

        CustomButton {

            id: info_message_ok_button
            button_width: parent.width/6
            button_height: button_width/2
            border_width: 0
            button_radius: 25
            button_text: "OK"
            text_color: "white"
            text_color_hovered: light_sand
            font_point_size: 15
            rect_color: orange
            rect_color_hovered: light_brown

            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: button_height/1.5

        }

    }

    Connections {

        target: info_message_ok_button

        function onButtonClickedSignal() {

            info_message.visible = false;

        }

    }

    Connections {

        target: login_page

        function onShowEmptyFieldsError(title, message) {

            info_message.info_message_title = title;
            info_message.info_message_text = message;

            info_message.visible = true;

        }

    }

    Connections {

        target: register_page

        function onShowEmptyFieldsError(title, message) {

            info_message.info_message_title = title;
            info_message.info_message_text = message;

            info_message.visible = true;

        }

    }

}
