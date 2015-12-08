\o tp3.html
 \pset format html
 \pset border 1
 \pset title 'TP3'
 \pset tableattr align='center'


--Requete numero 1
DROP TABLE IF EXISTS animal_bis;
CREATE TABLE animal_bis AS SELECT * FROM animal;

\qecho '<h1>Elements a supprimer</h1>'
\pset tableattr align='center'
--On verifie que les animaux dont le nom commence par P et n'ayant pas encore fait de visite existent pour pouvoir après les supprimer.
SELECT * FROM animal_bis
WHERE noman LIKE 'P%' 
AND idani NOT IN 	
		(SELECT DISTINCT idani FROM visite);

DELETE FROM animal_bis
WHERE noman LIKE 'P%' 
AND idani NOT IN
		 (SELECT DISTINCT idani FROM visite);

\qecho '<h1>Verification de la requete 1</h1>'
\pset tableattr align='center'
SELECT * FROM animal_bis 
WHERE noman LIKE 'P%' 
AND idani NOT IN 
		(SELECT DISTINCT idani FROM visite);

--Requete numero 2:

DROP TABLE IF EXISTS visite_bis;
CREATE TABLE visite_bis AS SELECT * FROM visite;

\qecho '<h1>Table copie</h1>'
\pset tableattr align='center'
SELECT * FROM visite_bis;

INSERT INTO visite_bis
VALUES ('2002168-01','PR002-01',TO_DATE('22-04-2002','DD-MM-YYYY'),'Examen',TO_DATE('02-05-2002','DD-MM-YYYY'),'Cheque',TO_DATE('22-04-2002','DD-MM-YYYY'),'150','O','Visite de routine');

INSERT INTO visite_bis(numvi,idani,detai)
VALUES ('2002168-01','AC001-01','Le paiement s''effectuera a la fin du mois');

\qecho '<h1>Verification de la requete 2</h1>'
\pset tableattr align='center'
SELECT * FROM visite_bis;

--Requete numero 3:
DROP TABLE IF EXISTS animal_bis;
CREATE TABLE animal_bis AS SELECT * FROM animal;

--Pour la supression on utilise DELETE FROM table et non TRUNCATE table qui elle garde les donnees dans la bdd sans pour autant les supprimer. Cette commande vide juste la table contrairement à la commande DELETE qui supprime les donnees meme de la bdd.
DELETE FROM animal_bis;

INSERT INTO animal_bis
SELECT * FROM animal 
WHERE noman LIKE 'P%' 
AND idani NOT IN 
		(SELECT DISTINCT idani FROM visite);

\qecho '<h1>Verification de la requete 3</h1>'
\pset tableattr align='center'
SELECT * FROM animal_bis ;

--Requete numero 4:
DROP TABLE IF EXISTS client_bis;
CREATE TABLE client_bis AS SELECT * FROM client;

\qecho '<h1>Table Client</h1>'
\pset tableattr align='center'
--Verification de la table
SELECT * FROM client_bis;

--Modification dans la table : 
UPDATE client_bis
SET typec=4, remis=remis*2
WHERE codep IN 
		(SELECT codep FROM departement WHERE depar='Gard');

\qecho '<h1>Verification de la requete 4</h1>'
\pset tableattr align='center'
SELECT * FROM client_bis;

--Requête numero 5: 
DROP TABLE IF EXISTS visite_bis;
CREATE TABLE visite_bis AS SELECT * FROM visite;

\pset tableattr align='center'
--Verification de la table
SELECT * FROM visite_bis;

--Modification de la table : 
UPDATE visite_bis AS v
SET detai='La somme restant due sera payee a la fin du mois'
WHERE v.monpa < ( SELECT SUM(t.prix)+SUM(COALESCE(m.prix,0))
		FROM detail_visite AS dv
		LEFT JOIN medicament AS m ON m.comed=dv.comed
		INNER JOIN traitement AS t ON t.cotra=dv.comed
		WHERE v.numvi=dv.numvi)
;
\qecho '<h1>Verification de la requete 5</h1>'
\pset tableattr align='center'
SELECT * FROM visite_bis;


--TRANSACTIONS
--Requete numero 6:
DROP TABLE IF EXISTS client_bis;
CREATE TABLE client_bis AS SELECT * FROM client;

BEGIN TRANSACTION;
DELETE FROM client_bis;
ROLLBACK;

--On verifie que la table n'est pas supprimée :
\qecho '<h1>Verification de la requete 6</h1>'
\pset tableattr align='center' 
SELECT * FROM client_bis;


--Requete numero 7: 

DROP TABLE IF EXISTS client_bis;
CREATE TABLE client_bis AS SELECT * FROM client;

BEGIN TRANSACTION;
DELETE FROM client_bis;
COMMIT;
ROLLBACK;
END;

--On verifie que la table est supprimée :
\qecho '<h1>Verification de la requete 7</h1>'
\pset tableattr align='center'

SELECT * FROM client_bis;

--Creation d'une sequence :
CREATE SEQUENCE seq_medicament
INCREMENT 1
START 1000
MAXVALUE 9000;

--IV. Utilisation pour insertions de lignes : 
DROP TABLE IF EXISTS medicament_bis;
CREATE TABLE medicament_bis AS SELECT * FROM medicament;

INSERT INTO medicament_bis(comed,medic,prix)
VALUES(NEXTVAL('seq_medicament'),'Pyralvex','6.00');
VALUES(NEXTVAL('seq_medicament'),'Muciclar - 25g','8.50');

--Verification :
\qecho '<h1>Verification de la requete </h1>'
\pset tableattr align='center'
 
SELECT * FROM medicament_bis;

--Affichage de la valeur courante de la sequence : 
SELECT CURRVAL('seq_medicament');

--V. Modification d'une sequence : 
DELETE FROM medicament_bis
WHERE comed='1000' OR comed='1001';

SELECT SETVAL('seq_medicament',1000);
INSERT INTO medicament_bis(comed,medic,prix)
VALUES(CURRVAL('seq_medicament'),'Biafine','4.00');

--VI. Supression de la sequence : 
DROP SEQUENCE seq_medicament;

--Création et supression de vues : 
--I. Creation d'une vue : 
DROP VIEW IF EXISTS clients_gard;

CREATE VIEW clients_gard AS SELECT
numcl AS "Num Client",
nomcl AS "Nom Client",
local AS "Localite"
FROM client
WHERE codep IN ( SELECT codep FROM departement 
		WHERE depar='Gard');

--Affichage de la vue : 
\qecho '<h1>Affichage de la vue 3</h1>'
\pset tableattr align='center'

SELECT * FROM clients_gard;

--Requete numero 2 :
CREATE VIEW visites_en_clair AS SELECT
a.idani AS "id_animal",
a.noman AS "nom_animal", a.numcl AS "numero_client",
v.numvi AS "numero_visite",
v.monpa AS "montant"
FROM animal a 
INNER JOIN visite v ON v.idani=a.idani
WHERE v.datev BETWEEN '2001-01-01' AND '2001-05-31';

--Verification de la vue : 
\qecho '<h1>Verification de la vue</h1>'
\pset tableattr align='center'

SELECT * FROM visites_en_clair;

--Requete numero 3:
DROP VIEW IF EXISTS depenses_clients; 

CREATE VIEW depenses_clients AS SELECT
c.nomcl AS "Nom du client",
COUNT(v.numvi) AS "Nombre de visite",
SUM(COALESCE(t.prix, 0)) AS "Prix total des traitements",
SUM(COALESCE(m.prix, 0)) AS "Prix total des medicaments",
SUM(COALESCE(m.prix, 0)) + SUM(COALESCE(t.prix, 0)) AS "Prix total general"
FROM client c
LEFT JOIN animal a ON a.numcl = c.numcl
LEFT JOIN visite v ON v.idani = a.idani
LEFT JOIN detail_visite dv ON dv.numvi = v.numvi
LEFT JOIN medicament m ON m.comed = dv.comed
LEFT JOIN traitement t ON t.cotra = dv.cotra
GROUP BY c.numcl;

--II. Extraction de donnees a partir d'une vue : 
--Requete numero 4 : 
SELECT DISTINCT "Nom Client" FROM clients_gard
WHERE "Nom Client" LIKE 'R%';

--Requete numero 5 :
SELECT noman FROM animal
WHERE numcl IN ( SELECT "Num Client" FROM clients_gard );

--Requete numero 6: 
DROP VIEW IF EXISTS visites_importantes; 

CREATE VIEW visites_importantes AS SELECT
"nom_animal",
"numero_visite",
"montant"
FROM visites_en_clair
WHERE "montant">'500';

--Affichage du contenu de la vue : 
\qecho '<h1>Affichage de la vue</h1>'
\pset tableattr align='center'

SELECT * FROM visites_importantes;

--Requete numero 7:
SELECT SUM(COALESCE("montant",0)) AS "Montant Total" 
FROM visites_en_clair
WHERE "numero_client" IN (SELECT "numero_client" FROM client 
		WHERE "nom_animal" LIKE 'George Grandjean')
GROUP BY "id_animal";

--Requete numero 8:
SELECT SUM("Prix total general")/COUNT(*)
FROM depenses_clients;

--Requete numero 9:
SELECT "Prix total general"
FROM depenses_clients
WHERE "Prix total general" > (SELECT SUM("Prix total general")/COUNT(*) FROM depenses_clients);


--III. Destruction de donnees à partir d'une vue:
--Requete numero 10: 
DROP VIEW clients_gard;
DROP VIEW visites_en_clair CASCADE;
DROP VIEW depenses_clients CASCADE;

 
\o
