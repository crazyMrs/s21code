SELECT p.name AS person_name, me.pizza_name, pi.name AS pizzeria_name
    FROM person_order
        JOIN person p ON person_id = p.id
        JOIN menu me ON menu_id = me.id
        JOIN pizzeria pi ON pizzeria_id = pi.id
ORDER BY person_name, pizza_name, pizzeria_name;