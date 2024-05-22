WITH order_vis AS ((SELECT pz.name, COUNT(*) AS count, 'order' AS action_type
                    FROM person_order po
                        JOIN menu m ON po.menu_id = m.id
                        JOIN pizzeria pz ON m.pizzeria_id = pz.id
                    GROUP BY pz.name
                    ORDER BY count DESC)
                    UNION
                    (SELECT pz.name, COUNT(*) AS count, 'visit' action_type
                    FROM person_visits pv
                        JOIN pizzeria pz ON pv.pizzeria_id = pz.id
                    GROUP BY pz.name
                    ORDER BY count DESC))

SELECT name, SUM(count) AS total_count
FROM order_vis
GROUP BY name
ORDER BY total_count DESC, name;