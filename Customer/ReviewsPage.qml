import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning

Page {

    id: reviews_page

    visible: false

    property string cafe_name
    property string cafe_address
    property string cafe_rating
    property int cafe_data_margins: 10

    Image {

        id: background_image

        source: "qrc:/Images/background.jpg"

        anchors.fill: parent

    }

    ListModel {

        id: reviews_model

    }

    Rectangle {

        id: reviews_rectangle
        width: main_window.width*0.95
        height: main_window.height*0.9
        color: pale

        clip: true

        anchors.centerIn: parent

        Rectangle {

            id: cafe_data_rectangle
            width: parent.width
            height: cafe_name_text.paintedHeight + cafe_address_text.paintedHeight + cafe_rating_text.paintedHeight +
                    cafe_name_text.anchors.topMargin * 3
            color: dark_brown

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            ReturnButton {

                id: reviews_return_button

                circle_radius: cafe_rating_text.paintedHeight*1.5
                circle_color: light_sand
                circle_color_hovered: orange
                line_width: 1
                lines_color: light_brown
                lines_color_hovered: pale

                anchors.top: parent.top
                anchors.right: parent.right
                anchors.margins: circle_radius/2

            }

            Text {

                id: cafe_name_text
                text: cafe_name
                color: yellow
                font.pointSize: 20
                font.bold: true
                font.underline: true

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: cafe_data_margins

            }

            Text {

                id: cafe_address_text
                text: cafe_address
                color: yellow
                font.pointSize: 14

                anchors.top: cafe_name_text.bottom
                anchors.left: cafe_name_text.left
                anchors.topMargin: cafe_data_margins

            }

            Text {

                id: cafe_rating_text
                text: cafe_rating
                color: yellow
                font.pointSize: 14

                anchors.verticalCenter: cafe_rating_star.verticalCenter
                anchors.right: cafe_rating_star.left
                anchors.rightMargin: cafe_data_margins

            }

            Star {

                id: cafe_rating_star
                star_color: yellow
                star_width: cafe_rating_text.paintedHeight

                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: cafe_data_margins

            }

        }

        ListView {

            id: reviews_view
            width: parent.width
            height: parent.height*0.7
            clip: true
            spacing: 5

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: cafe_data_rectangle.bottom

            model: reviews_model

            delegate: Rectangle {

                id: review_rectangle
                width: parent.width
                height: nickname.paintedHeight + review_text.paintedHeight + review_date_text.paintedHeight +
                        nickname.anchors.margins*4
                radius: 10
                border.width: 1
                border.color: dark_brown

                color: orange

                Text {

                    id: nickname
                    text: model.reviewer
                    font.pointSize: 18
                    font.bold: true
                    font.underline: true
                    color: pale

                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: 5

                }

                Text {

                    id: review_text
                    text: model.review_text
                    font.pointSize: 14
                    color: pale

                    anchors.top: nickname.bottom
                    anchors.topMargin: 5
                    anchors.left: nickname.left

                }

                Text {

                    id: review_date_text
                    text: model.review_date
                    font.pointSize: 14
                    color: pale

                    anchors.top: review_text.bottom
                    anchors.right: parent.right
                    anchors.margins: 5

                }

            }


        }

    }

    Connections {

        target: Client

        function onAddCafeReview(reviewer, cafe_id, star_rating, review_text, review_date) {

            reviews_model.append({ reviewer: reviewer, cafe_id: cafe_id, star_rating: star_rating,
                                   review_text: review_text, review_date: review_date });

        }

    }

    Connections {

        target: reviews_return_button

        function onReturnButtonClickedSignal() {

            stack_view.pop(map_page);
            reviews_model.clear();

        }

    }


}
