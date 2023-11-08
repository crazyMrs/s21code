SELECT pe.name AS person_name1, pn.name AS person_name2, pe.address AS common_address
FROM person pe
    JOIN person pn ON pe.address = pn.address AND pe.id > pn.id
ORDER BY person_name1, person_name2, common_address;
