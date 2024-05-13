import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning



Rectangle {

    id: star_rating
    width: star_width*5 + star_margin*5
    height: star_width
    color: background_rect_color

    property string background_rect_color
    property string non_hover_color
    property string hover_color

    property int star_width
    property int star_margin
    property int rating: 0
    property bool fixed: false

    Canvas {

        id: non_hovered_star1

        property int star_width: 100
        property string star_color: star_rating.non_hover_color

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: star_rating.star_margin/2

        width: star_rating.star_width
        height: star_rating.star_width

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }

    Canvas {

        id: hovered_star1

        property string star_color: star_rating.hover_color

        width: star_rating.star_width
        height: star_rating.star_width

        anchors.centerIn: non_hovered_star1

        visible: star_rating.rating >= 1

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }

    Canvas {

        id: non_hovered_star2

        property int star_width: 100
        property string star_color: star_rating.non_hover_color

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: non_hovered_star1.right
        anchors.leftMargin: star_rating.star_margin

        width: star_rating.star_width
        height: star_rating.star_width

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }


    Canvas {

        id: hovered_star2

        property string star_color: star_rating.hover_color

        width: star_rating.star_width
        height: star_rating.star_width

        anchors.centerIn: non_hovered_star2

        visible: star_rating.rating >= 2

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }

    Canvas {

        id: non_hovered_star3

        property int star_width: 100
        property string star_color: star_rating.non_hover_color

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: non_hovered_star2.right
        anchors.leftMargin: star_rating.star_margin

        width: star_rating.star_width
        height: star_rating.star_width

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }

    Canvas {

        id: hovered_star3

        property string star_color: star_rating.hover_color

        width: star_rating.star_width
        height: star_rating.star_width

        anchors.centerIn: non_hovered_star3

        visible: star_rating.rating >= 3

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }

    Canvas {

        id: non_hovered_star4

        property int star_width: 100
        property string star_color: star_rating.non_hover_color

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: non_hovered_star3.right
        anchors.leftMargin: star_rating.star_margin

        width: star_rating.star_width
        height: star_rating.star_width

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }

    Canvas {

        id: hovered_star4

        property string star_color: star_rating.hover_color

        width: star_rating.star_width
        height: star_rating.star_width

        anchors.centerIn: non_hovered_star4

        visible: star_rating.rating >= 4

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }

    Canvas {

        id: non_hovered_star5

        property int star_width: 100
        property string star_color: star_rating.non_hover_color

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: non_hovered_star4.right
        anchors.leftMargin: star_rating.star_margin

        width: star_rating.star_width
        height: star_rating.star_width

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }

    Canvas {

        id: hovered_star5

        property string star_color: star_rating.hover_color

        width: star_rating.star_width
        height: star_rating.star_width

        anchors.centerIn: non_hovered_star5

        visible: star_rating.rating >= 5

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star_color;
            ctx.fillStyle = star_color;
            ctx.lineWidth = 1;

            ctx.beginPath();

            ctx.moveTo(width/2, width*0.1);

            ctx.lineTo(width*0.25, width*0.9);
            ctx.lineTo(width*0.9, width*0.4);
            ctx.lineTo(width*0.1, width*0.4);
            ctx.lineTo(width*0.75, width*0.9);
            ctx.lineTo(width/2, width*0.1);

            ctx.fill();

        }

    }


    MouseArea {

        id: star_mouse_area

        hoverEnabled: true
        anchors.fill: parent

        onMouseXChanged: (mouse) => {

                             if (!star_rating.fixed) {

                                 if (mouse.x < (star_rating.star_width + star_rating.star_margin)/2) {

                                     star_rating.rating = 0;

                                 } else {

                                     star_rating.rating = mouse.x/(star_rating.star_width + star_rating.star_margin) + 1;

                                 }

                             }

                         }

        onContainsMouseChanged: {

            if (!containsMouse && !star_rating.fixed) {

                star_rating.rating = 0;

            }

        }

        onClicked: (mouse) => {

                       if (mouse.x < (star_rating.star_width + star_rating.star_margin)/2) {

                           star_rating.rating = 0;

                       } else {

                           star_rating.rating = mouse.x/(star_rating.star_width + star_rating.star_margin) + 1;

                       }

                       star_rating.fixed = true;
                       console.log(star_rating.rating);

                   }

    }
}
