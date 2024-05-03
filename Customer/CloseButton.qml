import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning


Item {

    id: close_button

    width: circle_radius
    height: circle_radius


    property int circle_radius
    property string circle_color
    property string circle_color_hovered
    property int line_width
    property int line_length: circle_radius - 15
    property string lines_color
    property string lines_color_hovered

    Rectangle {

        id: circle
        width: circle_radius
        height: circle_radius
        radius: circle_radius
        color: circle_color

        anchors.centerIn: parent

        Rectangle {

            id: hovered_circle
            width: 0
            height: width
            radius: width
            color: circle_color_hovered

            anchors.centerIn: parent

            state: "hidden"
            states: [

                State {
                    name: "shown"
                    when: close_button_mouse_area.containsMouse
                    PropertyChanges { target: hovered_circle; width: circle_radius }
                },

                State {
                    name: "hidden"
                    when: !close_button_mouse_area.containsMouse
                    PropertyChanges { target: hovered_circle; width: 0 }
                }

            ]

            transitions: Transition {
                PropertyAnimation { property: "width"; duration: 150; easing.type: Easing.InOutCubic }
            }


        }

        Rectangle {

            id: left_line
            width: line_length
            height: line_width
            color: close_button_mouse_area.containsMouse ? lines_color_hovered : lines_color

            anchors.centerIn: parent

            states: [

                State {

                    name: "rotated"
                    when: close_button_mouse_area.containsMouse
                    PropertyChanges { target: left_line; rotation: 135 }

                },

                State {

                    name: "non-rotated"
                    when: !close_button_mouse_area.containsMouse
                    PropertyChanges { target: left_line; rotation: 0 }

                }
            ]

            transitions: Transition {

                RotationAnimation { duration: 150; direction: RotationAnimation.Shortest }

            }

        }


        Rectangle {

            id: right_line
            width: line_length
            height: line_width
            color: close_button_mouse_area.containsMouse ? lines_color_hovered : lines_color

            anchors.centerIn: parent

            states: [

                State {

                    name: "rotated"
                    when: close_button_mouse_area.containsMouse
                    PropertyChanges { target: right_line; rotation: 45 }

                },

                State {

                    name: "non-rotated"
                    when: !close_button_mouse_area.containsMouse
                    PropertyChanges { target: right_line; rotation: 0 }

                }
            ]

            transitions: Transition {

                RotationAnimation { duration: 150; direction: RotationAnimation.Shortest }

            }

        }


    }

    MouseArea {

        id: close_button_mouse_area
        hoverEnabled: true
        anchors.fill: parent

    }

}
