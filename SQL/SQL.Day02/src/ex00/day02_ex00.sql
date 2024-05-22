SELECT name AS pizzeria_name, rating
FROM pizzeria pi
    LEFT JOIN person_visits p ON pi.id = p.pizzeria_id
WHERE pizzeria_id IS NULL;