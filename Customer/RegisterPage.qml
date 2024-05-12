import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning



Page {

    id: register_page

    visible: false

    property int input_line_thickness: 2

    signal showEmptyFieldsError(var error_title, var error_text);

    Image {

        id: background_image

        source: "qrc:/Images/background.jpg"

        anchors.fill: parent

    }

    Item {

        id: register_form
        width: main_window.width - 100
        height: register_header_rectangle.height + register_body_rectangle.height

        anchors.centerIn: parent

        Rectangle {

            id: register_header_rectangle
            width: parent.width
            height: main_window.height/6
            color: dark_brown
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top

            Text {

                id: register_title
                text: "Регистрация"
                font.pointSize: 30
                color: "white"

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: register_return_button.circle_radius/2

            }


            ReturnButton {

                id: register_return_button

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

            id: register_body_rectangle
            width: parent.width
            height: main_window.height/2
            color: pale

            anchors.horizontalCenter: register_header_rectangle.horizontalCenter
            anchors.top: register_header_rectangle.bottom

            Item {

                id: register_nickname_input_item
                width: register_body_rectangle.width/1.4
                height: register_nickname_input.font.pixelSize

                anchors.left: register_nickname_line.left
                anchors.top: parent.top
                anchors.topMargin: register_nickname_input.font.pixelSize*2


                TextInput {

                    id: register_nickname_input
                    //font.family: regular_font.name
                    font.pointSize: 22
                    selectionColor: dark_brown
                    selectedTextColor: light_sand

                    focus: true
                    anchors.fill: parent

                }

            }

            Canvas {

                id: register_nickname_line
                width: register_nickname_input_item.width
                height: input_line_thickness
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: register_nickname_input_item.bottom
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

                id: register_nickname_title

                text: "Имя пользователя"
                font.pointSize: 12
                color: dark_brown

                anchors.top: register_nickname_line.bottom
                anchors.topMargin: 5
                anchors.left: register_nickname_line.left

            }

            Item {

                id: register_password_input_item
                width: register_body_rectangle.width/1.4
                height: register_password_input.font.pixelSize

                anchors.left: register_password_line.left
                anchors.top: register_nickname_line.bottom
                anchors.topMargin: register_password_input.font.pixelSize*2


                TextInput {

                    id: register_password_input
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

                id: register_password_line
                width: register_password_input_item.width
                height: input_line_thickness
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: register_password_input_item.bottom
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

                id: register_password_title

                text: "Пароль"
                font.pointSize: 12
                color: dark_brown

                anchors.top: register_password_line.bottom
                anchors.topMargin: 5
                anchors.left: register_password_line.left

            }

            Item {

                id: register_password_confirmation_input_item
                width: register_body_rectangle.width/1.4
                height: register_password_input.font.pixelSize

                anchors.left: register_password_confirmation_line.left
                anchors.top: register_password_line.bottom
                anchors.topMargin: register_password_input.font.pixelSize*2


                TextInput {

                    id: register_password_confirmation_input
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

                id: register_password_confirmation_line
                width: register_password_confirmation_input_item.width
                height: input_line_thickness
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: register_password_confirmation_input_item.bottom
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

                id: register_password_confirmation_title

                text: "Подтверждение пароля"
                font.pointSize: 12
                color: dark_brown

                anchors.top: register_password_confirmation_line.bottom
                anchors.topMargin: 5
                anchors.left: register_password_confirmation_line.left

            }


            CustomButton {

                id: register_register_button

                button_width: register_body_rectangle.width/2
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
                anchors.bottom: parent.bottom
                anchors.bottomMargin: button_height*1.25

            }

        }

    }

    Connections {

        target: register_return_button

        function onReturnButtonClickedSignal() {

            register_nickname_input.clear();
            register_password_input.clear();
            register_password_confirmation_input.clear();

            stack_view.pop(main_page);

        }

    }

    Connections {

        target: register_register_button

        function onButtonClickedSignal() {

            if (register_nickname_input.text === "" ||
                register_password_input.text === "" ||
                register_password_confirmation_input.text === "") {

                showEmptyFieldsError("Ошибка регистрации", "Заполните все\nнеобходимые поля!");

            } else {

                Client.onRegister(register_nickname_input.text, register_password_input.text);

            }


        }

    }

}
