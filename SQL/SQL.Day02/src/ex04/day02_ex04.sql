SELECT pizza_name, pi.name AS pizzeria_name, price
FROM menu
    INNER JOIN pizzeria pi ON pi.id = pizzeria_id
WHERE pizza_name = 'pepperoni pizza' OR pizza_name = 'mushroom pizza'
ORDER BY pizza_name, pizzeria_name;