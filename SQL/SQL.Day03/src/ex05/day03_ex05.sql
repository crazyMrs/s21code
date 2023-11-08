SELECT pz.name AS pizzeria_name
FROM person p
	JOIN person_visits pv ON pv.person_id = p.id
	JOIN pizzeria pz ON pv.pizzeria_id = pz.id
WHERE p.name = 'Andrey'
EXCEPT
SELECT pz.name AS pizzeria_name
FROM person p
	JOIN person_order po ON po.person_id = p.id
	JOIN menu me ON po.menu_id = me.id
	JOIN pizzeria pz ON me.pizzeria_id = pz.id
WHERE p.name = 'Andrey'
ORDER BY 1;