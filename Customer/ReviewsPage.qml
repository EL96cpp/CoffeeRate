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
    property int cafe_rating
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

        id: map_rectangle
        width: main_window.width*0.95
        height: main_window.height*0.9
        radius: 10
        color: pale

        clip: true

        anchors.centerIn: parent

        Rectangle {

            id: cafe_data_rectangle
            width: parent.width*0.95
            height: cafe_name_text.paintedHeight + cafe_address_text.paintedHeight + cafe_rating_text.paintedHeight +
                    cafe_name_text.anchors.topMargin * 3
            radius: 10
            color: "red"

            anchors.top: parent.top
            //anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            Text {

                id: cafe_name_text
                text: cafe_name
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
                font.pointSize: 14

                anchors.top: cafe_name_text.bottom
                anchors.left: cafe_name_text.left
                anchors.topMargin: cafe_data_margins

            }

            Text {

                id: cafe_rating_text
                text: cafe_rating
                font.pointSize: 14

                anchors.verticalCenter: cafe_rating_star.verticalCenter
                anchors.right: cafe_rating_star.left
                anchors.rightMargin: cafe_data_margins

            }

            Star {

                id: cafe_rating_star
                star_width: cafe_rating_text.paintedHeight

                anchors.right: parent.right
                anchors.top: cafe_address_text.bottom
                anchors.margins: cafe_data_margins

            }

        }

    }

    Connections {

        target: Client

        function onAddCafeReview(reviewer, cafe_id, star_rating, review_text, review_date) {

            reviews_model.append({ reviewer: reviewer, cafe_id: cafe_id, star_rating: star_rating,
                                   review_text: review_text, review_date: review_date });

            console.log(reviewer + " " + cafe_id + " " + star_rating + " " + review_text + " " + review_date);

        }

    }


}
