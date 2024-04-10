SELECT name from people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id in
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = 'Kevin Bacon')))
AND name != 'Kevin Bacon';


-- SELECT p.name
-- FROM people p
-- JOIN stars s1 ON p.id = s1.person_id
-- JOIN stars s2 ON s1.movie_id = s2.movie_id
-- JOIN people kb ON s2.person_id = kb.id
-- WHERE kb.name = 'Kevin Bacon'
-- AND p.name != 'Kevin Bacon';
