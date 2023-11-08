SELECT pn.name AS object_name
    FROM (SELECT name FROM person ORDER BY name) AS pn
UNION ALL
SELECT mp.pizza_name AS object_name 
    FROM (SELECT pizza_name FROM menu ORDER BY pizza_name) AS mp;