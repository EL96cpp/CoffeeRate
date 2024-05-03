import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning



Page {

    id: login_page

    visible: false

    property int input_line_thickness: 2

    Image {

        id: background_image

        source: "qrc:/Images/background.jpg"

        anchors.fill: parent

    }

    Item {

        id: login_form
        width: main_window.width - 100
        height: login_header_rectangle.height + login_body_rectangle.height

        anchors.centerIn: parent


        Rectangle {

            id: login_header_rectangle
            width: parent.width
            height: main_window.height/6
            color: dark_brown
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top

            Text {

                id: login_title
                text: "Авторизация"
                font.pointSize: 30
                color: "white"

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: login_return_button.circle_radius/2

            }


            ReturnButton {

                id: login_return_button

                circle_radius: 50
                circle_color: light_sand
                circle_color_hovered: orange
                line_width: 2
                lines_color: light_brown
                lines_color_hovered: pale

                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: circle_radius/2

            }


        }

        Rectangle {

            id: login_body_rectangle
            width: parent.width
            height: main_window.height/2
            color: pale

            anchors.horizontalCenter: login_header_rectangle.horizontalCenter
            anchors.top: login_header_rectangle.bottom

            Item {

                id: login_nickname_input_item
                width: login_body_rectangle.width/1.4
                height: login_nickname_input.font.pixelSize

                anchors.left: login_nickname_line.left
                anchors.top: parent.top
                anchors.topMargin: login_nickname_input.font.pixelSize*3


                TextInput {

                    id: login_nickname_input
                    //font.family: regular_font.name
                    font.pointSize: 22
                    selectionColor: dark_brown
                    selectedTextColor: light_sand

                    focus: true
                    anchors.fill: parent

                }

            }

            Canvas {

                id: login_nickname_line
                width: login_nickname_input_item.width
                height: input_line_thickness
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: login_nickname_input_item.bottom
                anchors.topMargin: 10

                onPaint: {

                    var ctx = getContext("2d")

                    ctx.strokeStyle = "#300d00"
                    ctx.lineWidth = 10

                    ctx.beginPath()

                    ctx.moveTo(0, 0)
                    ctx.lineTo(width, 0)

                    ctx.stroke()

                }
            }

            Text {

                id: login_nickname_title

                text: "Имя пользователя"
                font.pointSize: 12
                color: dark_brown

                anchors.top: login_nickname_line.bottom
                anchors.topMargin: 5
                anchors.left: login_nickname_line.left

            }

            Item {

                id: login_password_input_item
                width: login_body_rectangle.width/1.4
                height: login_password_input.font.pixelSize

                anchors.left: login_password_line.left
                anchors.top: login_nickname_line.bottom
                anchors.topMargin: login_password_input.font.pixelSize*3


                TextInput {

                    id: login_password_input
                    //font.family: regular_font.name

                    font.pointSize: 22
                    echoMode: TextInput.Password
                    selectionColor: dark_brown
                    selectedTextColor: light_sand

                    focus: true
                    anchors.fill: parent

                }

            }

            Canvas {

                id: login_password_line
                width: login_password_input_item.width
                height: input_line_thickness
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: login_password_input_item.bottom
                anchors.topMargin: 10

                onPaint: {

                    var ctx = getContext("2d")

                    ctx.strokeStyle = "#300d00"
                    ctx.lineWidth = 10

                    ctx.beginPath()

                    ctx.moveTo(0, 0)
                    ctx.lineTo(width, 0)

                    ctx.stroke()

                }
            }

            Text {

                id: login_password_title

                text: "Пароль"
                font.pointSize: 12
                color: dark_brown

                anchors.top: login_password_line.bottom
                anchors.topMargin: 5
                anchors.left: login_password_line.left

            }


            CustomButton {

                id: login_login_button

                button_width: login_body_rectangle.width/2
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
                anchors.bottom: parent.bottom
                anchors.bottomMargin: button_height*2

            }

        }


    }

    Connections {

        target: login_return_button

        function onReturnButtonClickedSignal() {

            login_nickname_input.clear();
            login_password_input.clear();

            stack_view.pop(main_page);

        }


    }


}
