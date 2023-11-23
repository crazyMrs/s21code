SELECT p.name, m.pizza_name, m.price, (m.price * (100 - pd.discount)) / 100 AS discount_price, pz.name AS pizzeria_name
FROM person_discounts pd
    JOIN person p ON pd.person_id = p.id
    JOIN menu m ON pd.pizzeria_id = m.pizzeria_id
    JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY 1, 2;
