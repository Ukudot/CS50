SELECT ROUND(AVG(rating), 1) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);
