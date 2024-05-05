CREATE DATABASE coffee_rate;
\c coffee_rate;
CREATE TABLE users (nickname TEXT, password TEXT);
CREATE TABLE cafes (name_of_cafe TEXT, city TEXT, street TEXT, house_number INT);
CREATE TABLE reviews (reviewer TEXT, name_of_cafe TEXT, city TEXT, street TEXT, house_number INT, star_rating INT, review_text TEXT);
