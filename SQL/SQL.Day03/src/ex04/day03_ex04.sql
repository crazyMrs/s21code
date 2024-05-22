(SELECT pz.name AS pizzeria_name
FROM pizzeria pz
 	JOIN menu me ON pz.id = me.pizzeria_id
    JOIN person_order po ON me.id = po.menu_id
    JOIN person p ON po.person_id = p.id
WHERE gender = 'female' 
EXCEPT
SELECT pz.name AS pizzeria_name
FROM pizzeria pz
    JOIN menu me ON pz.id = me.pizzeria_id
    JOIN person_order po ON me.id = po.menu_id
    JOIN person p ON po.person_id = p.id
  WHERE gender = 'male')
UNION
(SELECT pz.name AS pizzeria_name
FROM pizzeria pz
    JOIN menu me ON pz.id = me.pizzeria_id
    JOIN person_order po ON me.id = po.menu_id
    JOIN person p ON po.person_id = p.id
WHERE gender = 'male' 
EXCEPT
SELECT pz.name AS pizzeria_name
FROM pizzeria pz
    JOIN menu me ON pz.id = me.pizzeria_id
    JOIN person_order po ON me.id = po.menu_id
    JOIN person p ON po.person_id = p.id
WHERE gender = 'female')
ORDER BY 1;