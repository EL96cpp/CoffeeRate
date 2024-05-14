#include "cafereview.h"


CafeReview::CafeReview(const QString &reviewer_nickname,
                       const QString &cafe_id,
                       const QString &star_rating,
                       const QString &review_text,
                       const QString &review_date) : reviewer_nickname(reviewer_nickname), cafe_id(cafe_id),
                                                     star_rating(star_rating), review_text(review_text),
                                                     review_date(review_date) {}

QString CafeReview::GetReviewerNickname() const {

    return reviewer_nickname;

}

QString CafeReview::GetCafeId() const {

    return cafe_id;

}

QString CafeReview::GetStarRating() const {

    return star_rating;

}

QString CafeReview::GetReviewText() const {

    return review_text;

}

QString CafeReview::GetReviewDate() const {

    return review_date;

}
