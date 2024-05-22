ALTER TABLE person_discounts ADD CONSTRAINT ch_nn_person_id CHECK (person_id IS NOT NULL);
ALTER TABLE person_discounts ADD CONSTRAINT ch_nn_pizzeria_id CHECK (pizzeria_id IS NOT NULL);
ALTER TABLE person_discounts ADD CONSTRAINT ch_nn_discount CHECK (discount IS NOT NULL);
ALTER TABLE person_discounts ALTER COLUMN discount SET DEFAULT 0;
ALTER TABLE person_discounts ADD CONSTRAINT ch_range_discount CHECK (discount >= 0 AND discount <= 100);


-- ALTER TABLE person_discounts
--     DROP CONSTRAINT ch_nn_person_id,
--     DROP CONSTRAINT ch_nn_pizzeria_id,
--     DROP CONSTRAINT ch_nn_discount,
--     ALTER COLUMN discount DROP DEFAULT,
--     DROP CONSTRAINT ch_range_discount;
