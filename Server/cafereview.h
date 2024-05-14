#ifndef CAFEREVIEW_H
#define CAFEREVIEW_H

#include <QString>

class CafeReview {

public:
    CafeReview(const QString& reviewer_nickname, const QString& cafe_id, const QString& star_rating,
               const QString& review_text, const QString& review_date);

    QString GetReviewerNickname() const;
    QString GetCafeId() const;
    QString GetStarRating() const;
    QString GetReviewText() const;
    QString GetReviewDate() const;

private:
    QString reviewer_nickname;
    QString cafe_id;
    QString star_rating;
    QString review_text;
    QString review_date;

};

#endif // CAFEREVIEW_H
