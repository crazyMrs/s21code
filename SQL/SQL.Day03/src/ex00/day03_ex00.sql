SELECT me.pizza_name, me.price, pz.name AS pizzeria_name, pv.visit_date
FROM person p
	JOIN person_visits pv ON p.id = pv.person_id
	JOIN pizzeria pz ON pv.pizzeria_id = pz.id
	JOIN menu me ON pz.id = me.pizzeria_id
WHERE p.name = 'Kate' AND (price >= 800 AND price <= 1000)
ORDER BY 1, 2, 3;