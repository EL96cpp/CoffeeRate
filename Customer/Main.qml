import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning



Window {

    id: main_window

    width: 576
    height: 1024
    visible: true
    title: qsTr("CoffeeRate")

    FontLoader {

        id: logo_font
        source: "qrc:/Fonts/Font.otf"

    }

    Image {

        id: bk

        source: "qrc:/Images/background.jpg"

        anchors.fill: parent

    }

    StackView {

        id: stack_view
        anchors.fill: parent
        initialItem: main_page

    }


    Page {

        id: main_page

        visible: true
        anchors.fill: parent

        Image {

            id: background_image

            source: "qrc:/Images/background.jpg"

            anchors.fill: parent

        }

        Rectangle {

            id: main_logo_rectangle

            width: main_window.width
            height: main_logo_text.paintedHeight
            color: "#452f2d"


            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: main_page.height/8

            Text {

                id: main_logo_text
                text: "CoffeeRate"
                color: "white"
                font.family: logo_font.name
                font.pointSize: 80
                font.bold: true
                horizontalAlignment: Text.AlignHCenter

                anchors.centerIn: parent

            }

        }

        Rectangle {

            id: main_menu_rectangle
            width: main_logo_rectangle.width - 50
            height: main_page.height/2.5

            color: "#50351e1c"

            anchors.top: main_logo_rectangle.bottom
            anchors.topMargin: main_logo_rectangle.height/2
            anchors.horizontalCenter: parent.horizontalCenter

            CustomButton {

                id: login_button

                button_width: 300
                button_height: 50
                border_width: 0
                button_radius: 25
                button_text: "Вход"
                text_color: "#452f2d"
                text_color_hovered: "#b19877"
                font_point_size: 15
                rect_color: "white"
                rect_color_hovered: "#452f2d"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: (main_window.height/3 - button_height*3)/4

            }

            CustomButton {

                id: register_button

                button_width: 300
                button_height: 50
                border_width: 0
                button_radius: 25
                button_text: "Регистрация"
                text_color: "#452f2d"
                text_color_hovered: "#b19877"
                font_point_size: 15
                rect_color: "white"
                rect_color_hovered: "#452f2d"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: login_button.bottom
                anchors.topMargin: (main_window.height/3 - button_height*3)/4

            }

            CustomButton {

                id: exit_button

                button_width: 300
                button_height: 50
                border_width: 0
                button_radius: 25
                button_text: "Выход"
                text_color: "#452f2d"
                text_color_hovered: "#b19877"
                font_point_size: 15
                rect_color: "white"
                rect_color_hovered: "#452f2d"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: register_button.bottom
                anchors.topMargin: (main_window.height/3 - button_height*3)/4

            }

        }

    }

    Connections {

        target: login_button
        function onButtonClickedSignal() {

            console.log("Login button clicked");

        }

    }

    Connections {

        target: register_button
        function onButtonClickedSignal() {

            console.log("Register button clicked");

        }

    }

    Connections {

        target: exit_button
        function onButtonClickedSignal() {

            console.log("Exit button clicked");

        }

    }

}

