SELECT od.order_date, CONCAT(pe.name, ' (age:', pe.age, ')') AS person_information 
    FROM person_order od
    JOIN person pe ON od.person_id = pe.id
ORDER BY order_date, person_information;