SELECT me.pizza_name, me.price, pz.name AS pizzeria_name
FROM menu me
	LEFT JOIN person_order po ON me.id = po.menu_id
	JOIN pizzeria pz ON me.pizzeria_id  = pz.id
WHERE po.id IS NULL
ORDER BY 1, 2;