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

    property string dark_brown: "#351e1c"
    property string light_brown: "#452f2d"
    property string light_sand: "#c8b69f"
    property string orange: "#a55e47"
    property string pale: "#efede6"

    FontLoader {

        id: logo_font
        source: "qrc:/Fonts/Font.otf"

    }

    Image {

        id: background_image

        source: "qrc:/Images/background.jpg"

        anchors.fill: parent

    }

    StackView {

        id: stack_view
        anchors.fill: parent
        initialItem: main_page

        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 1
            }
        }
        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 1
            }
        }
        popEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 1
            }
        }
        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 1
            }
        }

    }


    MainPage {
        id: main_page
    }

    LoginPage {
        id: login_page
    }

    RegisterPage {
        id: register_page
    }

    MapPage {
        id: map_page
    }

    ReviewsPage {
        id: reviews_page
    }

    InfoMessage {
        id: info_message
    }


}

