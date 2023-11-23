CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
    IN pperson varchar DEFAULT 'Dmitriy',
    IN pprice numeric DEFAULT 500,
    IN pdate date DEFAULT '2022-01-08')
RETURNS TABLE (name varchar) AS $$
    BEGIN
        RETURN QUERY
        SELECT pizzeria.name
        FROM person_visits
            INNER JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
            INNER JOIN menu ON pizzeria.id = menu.pizzeria_id
            INNER JOIN person ON person_visits.person_id = person.id
        WHERE price < pprice AND person.name = pperson AND person_visits.visit_date = pdate;
    END;
$$ LANGUAGE plpgsql;

select *
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');
