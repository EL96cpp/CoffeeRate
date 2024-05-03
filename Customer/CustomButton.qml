import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning



Item {

    id: custom_button

    width: button_width
    height: button_height

    property int button_width
    property int button_height
    property int border_width
    property int button_radius
    property string button_text
    property string text_color
    property string text_color_hovered
    property int font_point_size
    property string rect_color
    property string rect_color_hovered

    signal buttonClickedSignal();

    Rectangle {

        id: basic_rectangle
        width: button_width
        height: button_height
        radius: button_radius
        color: rect_color
        border.width: border_width

        anchors.centerIn: parent

        Rectangle {

            id: inner_rectangle
            width: 0
            height: button_height-2*border_width
            radius: button_radius
            color: rect_color_hovered

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: border_width

            state: "hidden"
            states: [

                State {
                    name: "shown"
                    when: button_mouse_area.containsMouse
                    PropertyChanges { target: inner_rectangle; width: basic_rectangle.width }
                },

                State {
                    name: "hidden"
                    when: !button_mouse_area.containsMouse
                    PropertyChanges { target: inner_rectangle; width: 0 }
                }

            ]

            transitions: Transition {
                PropertyAnimation { property: "width"; duration: 250; easing.type: Easing.InOutCubic }
            }


        }


        Text {

            id: custom_button_text
            text: button_text
            color: button_mouse_area.containsMouse ? text_color_hovered : text_color
            font.pointSize: font_point_size
            anchors.centerIn: parent

        }

        MouseArea {

            id: button_mouse_area
            hoverEnabled: true
            anchors.fill: parent

            onClicked: {

                buttonClickedSignal();

            }

        }

    }



}
