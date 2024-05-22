SELECT pz.name AS pizzeria_name
FROM person pe
    INNER JOIN person_visits pv ON pe.id = pv.person_id
    INNER JOIN pizzeria pz ON pv.pizzeria_id = pz.id
    INNER JOIN menu me ON pz.id = me.pizzeria_id AND me.price < 800
WHERE pe.name = 'Dmitriy' AND pv.visit_date = '2022-01-08';