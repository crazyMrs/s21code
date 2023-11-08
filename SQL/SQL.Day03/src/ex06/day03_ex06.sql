SELECT DISTINCT me.pizza_name, p.name AS pizzeria_name_1, p1.name AS pizzeria_name_2, me.price
FROM menu me
	JOIN pizzeria p ON me.pizzeria_id = p.id
	JOIN pizzeria p1 ON me.pizzeria_id != p1.id
	JOIN menu m1 ON me.price = m1.price AND me.pizza_name = m1.pizza_name AND p1.id = m1.pizzeria_id
WHERE p1.id < p.id
ORDER BY 1;