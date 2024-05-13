import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning



Item {

    id: star
    width: star_width
    height: star_width

    property int star_width
    property string star_color

    Canvas {

        id: star_canvas
        width: star.star_width
        height: star.star_width

        anchors.centerIn: parent

        onPaint: {

            var ctx = getContext("2d")

            ctx.strokeStyle = star.star_color;
            ctx.fillStyle = star.star_color;
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

}
