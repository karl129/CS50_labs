SELECT sum(energy)/count(energy) AS average_energy FROM songs JOIN artists ON artist_id = artists.id WHERE artists.name = 'Drake';
