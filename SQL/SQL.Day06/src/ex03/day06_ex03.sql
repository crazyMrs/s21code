CREATE UNIQUE INDEX idx_person_discounts_unique 
    ON person_discounts (person_id, pizzeria_id);

SET enable_seqscan = OFF;
EXPLAIN ANALYSE
SELECT person_id, discount
FROM person_discounts
WHERE person_id = 5
   AND pizzeria_id = 12;


--DROP INDEX idx_person_discounts_unique
