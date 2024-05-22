SELECT pe.name
FROM person pe
    INNER JOIN person_order po ON pe.id = po.person_id
    INNER JOIN menu me ON po.menu_id = me.id
WHERE pe.gender = 'female' 
  AND me.pizza_name IN ('pepperoni pizza', 'cheese pizza')
ORDER BY pe.name;