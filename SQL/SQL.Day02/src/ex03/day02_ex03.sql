WITH ge AS (SELECT ge::date AS missing_date FROM generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day') AS ge)
SELECT missing_date::date
    FROM ge
        LEFT JOIN (SELECT visit_date FROM person_visits WHERE (person_id = 1 OR person_id = 2)) AS pe
        ON ge.missing_date = pe.visit_date
    WHERE visit_date IS NULL
ORDER BY missing_date;
