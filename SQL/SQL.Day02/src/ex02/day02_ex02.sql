SELECT (CASE WHEN pe.name IS NULL THEN '-' ELSE pe.name END) AS person_name, 
    visit_date, 
    (CASE WHEN pz.name IS NULL THEN '-' ELSE pz.name END) AS pizzeria_name
FROM (SELECT * FROM person_visits WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') AS vd
    FULL OUTER JOIN person pe ON vd.person_id = pe.id
    FULL OUTER JOIN pizzeria pz ON vd.pizzeria_id = pz.id
ORDER BY person_name, visit_date, pizzeria_name;