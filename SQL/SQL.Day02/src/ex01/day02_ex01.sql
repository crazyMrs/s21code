SELECT ge::date AS missing_date
    FROM (SELECT visit_date FROM person_visits WHERE (person_id = 1 OR person_id = 2)) AS pe
        RIGHT JOIN generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day') AS ge
        ON DATE (ge::date) = pe.visit_date
    WHERE visit_date IS NULL
ORDER BY missing_date;
