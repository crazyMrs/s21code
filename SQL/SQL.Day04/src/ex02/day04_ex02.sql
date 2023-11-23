CREATE VIEW v_generated_dates 
AS (
SELECT gs::date
FROM generate_series('2022-01-01'::date, '2022-01-31'::date, interval '1 day') as gs
ORDER BY gs::date);