SELECT pe.name
FROM person pe
    INNER JOIN person_order po ON pe.id = po.person_id
    INNER JOIN menu me ON po.menu_id = me.id
WHERE pe.address IN ('Moscow', 'Samara')
  AND pe.gender = 'male' 
  AND me.pizza_name IN ('pepperoni pizza', 'mushroom pizza')
ORDER BY pe.name DESC;