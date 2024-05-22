SELECT me.id
FROM  menu me
	LEFT JOIN person_order po ON me.id = po.menu_id
WHERE po.id IS NULL
ORDER BY 1;