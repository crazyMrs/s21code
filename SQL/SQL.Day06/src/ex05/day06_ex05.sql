COMMENT ON TABLE person_discounts IS 'Персональная скидка клиента';
COMMENT ON COLUMN person_discounts.id IS 'Основной ключ';
COMMENT ON COLUMN person_discounts.person_id IS 'Внешний ключ к человеку';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Внешний ключ к пиццерии';
COMMENT ON COLUMN person_discounts.discount IS 'Размер скидки';


-- COMMENT ON TABLE person_discounts IS '';
-- COMMENT ON COLUMN person_discounts.id IS '';
-- COMMENT ON COLUMN person_discounts.person_id IS '';
-- COMMENT ON COLUMN person_discounts.pizzeria_id IS '';
-- COMMENT ON COLUMN person_discounts.discount IS '';
