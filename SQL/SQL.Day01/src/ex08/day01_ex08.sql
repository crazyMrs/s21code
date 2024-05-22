SELECT od.order_date, CONCAT(pe.name, ' (age:', pe.age, ')') AS person_information 
    FROM person_order od
    NATURAL JOIN (SELECT id AS person_id, age, name FROM person) AS pe
ORDER BY 1, 2;