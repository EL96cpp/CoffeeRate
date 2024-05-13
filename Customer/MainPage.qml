import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning



Page {

    id: main_page

    visible: true

    property int buttons_height: 50
    property int buttons_margin: (main_menu_rectangle.height - buttons_height*3)/4

    Image {

        id: background_image

        source: "qrc:/Images/background.jpg"

        anchors.fill: parent

    }

    Rectangle {

        id: main_logo_rectangle

        width: main_window.width
        height: main_logo_text.paintedHeight
        color: dark_brown


        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: main_page.height/10

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
        height: main_page.height/2

        gradient: Gradient {

            GradientStop { position: 0.0; color: "#efede6" }
            GradientStop { position: 0.7; color: "#a0efede6" }
            GradientStop { position: 0.8; color: "#90efede6" }
            GradientStop { position: 0.9; color: "#50efede6" }
            GradientStop { position: 1.0; color: "#05efede6" }
            orientation: Gradient.Vertical

        }

        anchors.top: main_logo_rectangle.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        CustomButton {

            id: login_button

            button_width: 300
            button_height: 50
            border_width: 0
            button_radius: 25
            button_text: "Вход"
            text_color: light_sand
            text_color_hovered: "white"
            font_point_size: 15
            rect_color: light_brown
            rect_color_hovered: orange

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: button_height

        }

        CustomButton {

            id: register_button

            button_width: 300
            button_height: 50
            border_width: 0
            button_radius: 25
            button_text: "Регистрация"
            text_color: light_sand
            text_color_hovered: "white"
            font_point_size: 15
            rect_color: light_brown
            rect_color_hovered: orange


            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: login_button.bottom
            anchors.topMargin: button_height

        }

        CustomButton {

            id: exit_button

            button_width: 300
            button_height: 50
            border_width: 0
            button_radius: 25
            button_text: "Выход"
            text_color: light_sand
            text_color_hovered: "white"
            font_point_size: 15
            rect_color: light_brown
            rect_color_hovered: orange


            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: register_button.bottom
            anchors.topMargin: button_height

        }

    }

    Star {
        id: star
        star_width: 55
        star_color: orange
    }

    /*
    StarRating {

        id: star_rating

        non_hover_color: light_sand
        hover_color: dark_brown
        background_rect_color: "#50ffffff"

        star_width: 50
        star_margin: 5

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

    }
    */

    Connections {

        target: login_button
        function onButtonClickedSignal() {

            stack_view.push(login_page);

        }

    }

    Connections {

        target: register_button
        function onButtonClickedSignal() {

            stack_view.push(register_page);

        }

    }

    Connections {

        target: exit_button
        function onButtonClickedSignal() {

            Qt.callLater(Qt.quit);

        }

    }

}
