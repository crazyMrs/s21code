CREATE INDEX idx_person_name ON person USING btree (upper(name));

SET enable_seqscan = OFF;
EXPLAIN ANALYZE
SELECT name
FROM person
ORDER BY upper(name);

--DROP INDEX idx_person_name