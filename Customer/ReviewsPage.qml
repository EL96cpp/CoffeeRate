import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtLocation
import QtPositioning

Page {

    id: reviews_page

    ListModel {

        id: reviews_model

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
