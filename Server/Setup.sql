CREATE DATABASE coffee_rate;
\c coffee_rate;
CREATE TABLE users (nickname TEXT, password TEXT);
CREATE TABLE cafes (id SERIAL, name_of_cafe TEXT, city TEXT, street TEXT, house_number INT, latitude FLOAT, longitude FLOAT);
CREATE TABLE reviews (reviewer TEXT, cafe_id INT, star_rating INT, review_text TEXT, review_date TIMESTAMP WITHOUT TIME ZONE);
