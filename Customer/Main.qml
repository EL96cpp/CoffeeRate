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




}

