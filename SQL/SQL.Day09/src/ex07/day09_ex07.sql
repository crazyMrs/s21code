CREATE OR REPLACE FUNCTION func_minimum(arr FLOAT[])
RETURNS FLOAT AS $$
DECLARE
    result FLOAT;
BEGIN
    SELECT MIN(val) INTO result FROM unnest(arr) val;
    RETURN result;
END;
$$ LANGUAGE plpgsql;


SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);


