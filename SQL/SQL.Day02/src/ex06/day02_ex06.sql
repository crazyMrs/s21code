SELECT me.pizza_name, pz.name AS pizzeria_name
FROM person
    INNER JOIN person_order po ON person.id = po.person_id
    INNER JOIN menu me ON me.id = po.menu_id
    INNER JOIN pizzeria pz ON pz.id = me.pizzeria_id
WHERE person.name IN ('Anna', 'Denis')
ORDER BY pizza_name, pizzeria_name;