CREATE OR REPLACE FUNCTION fnc_fibonacci(IN pstop INTEGER DEFAULT 10)
RETURNS TABLE (A INTEGER) AS $$
WITH RECURSIVE R(A, B) AS (
    SELECT 0 AS A, 1 AS B
    UNION ALL
    SELECT B, A + B
    FROM R
    WHERE B < pstop
)
SELECT A
FROM R;
$$ LANGUAGE sql;

select * from fnc_fibonacci(100);

-- DROP FUNCTION IF EXISTS fnc_fibonacci;