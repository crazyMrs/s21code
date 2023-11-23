INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
SELECT (SELECT MAX(id) FROM person_visits) + 1, (SELECT id FROM person WHERE name = 'Dmitriy'), 
		(SELECT pizzeria_id FROM menu WHERE price < 800 AND pizzeria_id <> 4 LIMIT 1), '2022-01-08'::date;

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;
