SELECT title FROM movies WHERE id = (SELECT movie_id FROM ratings WHERE ratings.rating = 10.0);
