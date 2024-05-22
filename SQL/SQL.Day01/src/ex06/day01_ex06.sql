SELECT order_date AS action_date, name AS person_name FROM person_order AS od
    JOIN person pe ON od.person_id = pe.id
INTERSECT
SELECT visit_date, name AS person_name FROM person_visits AS vd
    JOIN person pv ON vd.person_id = pv.id
ORDER BY action_date ASC, person_name DESC;