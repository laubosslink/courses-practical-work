-- Voici le TP1, GR2, BDD
-- @file queries.sql
-- @author EL HIMDI Yasmine <yasmine.elhimdi@ecole.ensicaen.fr>
-- @author PARMENTIER Laurent <laubosslink@society-lbl.com> 


\o tp1-postgres.html
\pset format html
\pset border 1
\pset tableattr align='center'

\qecho '<p>Menu : </p>'
\qecho '<ul>'
\qecho '<li><a href="#animal">Animal</a></li>'
\qecho '<li><a href="#client">Client</a></li>'
\qecho '<li><a href="#departement">Departement</a></li>'
\qecho '<li><a href="#detail_visite">Detail visite</a></li>'
\qecho '<li><a href="#medicament">Medicament</a></li>'
\qecho '<li><a href="#traitement">Traitement</a></li>'
\qecho '<li><a href="#type_animal">Type animal</a></li>'
\qecho '<li><a href="#visite">Visite</a></li>'
\qecho '</ul>'

-- Tables :

\d

-- Table Animal :

\qecho '<a name="animal"Animal"></a>'
\d animal

-- Table Client :
\qecho '<a name="client"Client"></a>'
\d client
SELECT * FROM client;

-- Table departement :
\qecho '<a name="departement"Departement"></a>'
\d departement
SELECT * FROM departement;

-- Table detail_visites :
\qecho '<a name="detail_visite"Detail Visite"></a>'
\d detail_visite
SELECT * FROM detail_visite;

-- Table medicaments :
\qecho '<a name="medicament"Medicament"></a>'
\d medicament
SELECT * FROM medicament;

-- Table traitement :
\qecho '<a name="traitement"Traitement"></a>'
\d traitement
SELECT * FROM traitement;

-- Table type_animal :
\qecho '<a name="type_animal"Type Animal"></a>'
\d type_animal
SELECT * FROM type_animal;

-- Table visite :
\qecho '<a name="visite"Visite"></a>'
\d visite
SELECT * FROM visite;

-- Req n°1
SELECT nomcl AS "Nom Client" FROM client;

-- Req n°2

SELECT DISTINCT local AS "Localites" FROM client;

-- Req n°3

SELECT idani AS "Numero", noman AS "Nom", poids AS "pods", taill AS "Taille"
FROM animal
ORDER BY poids, taill DESC;

-- Req n°4

SELECT numcl AS "Numero", nomcl AS "Nom", typec AS "Type"
FROM client
WHERE local = 'Nimes';

-- Req n°5

SELECT idani AS "Numero", noman AS "Nom", poids AS "Poids"
FROM animal
WHERE poids > 200;

-- Req n°6

SELECT idani AS "Numero", noman AS "Nom", poids AS "Poids", taill AS "Taille"
FROM animal
WHERE poids >= taill*2;

-- Req n°7
SELECT comed AS "Numero", medic AS "Nom", prix AS "Prix"
FROM medicament
ORDER BY prix DESC
LIMIT 5;

-- Req n°8
SELECT comed AS "Numero", medic AS "Nom", prix AS "Prix"
FROM medicament
WHERE prix BETWEEN 100 AND 150;

-- Req n°9
SELECT idani AS "Numero", noman AS "Nom", coule AS "Couleur"
FROM animal
WHERE Coule IN ('Blanc', 'Gris',  'Noir');

-- Req n°10
SELECT numcl AS "Numero", nomcl AS "Nom"
FROM client
WHERE nomcl LIKE 'Zoo%';

-- Req n°11
SELECT idani AS "Numero", noman AS "Nom"
FROM animal
WHERE race IS NULL;

-- Req n°12
-- Remarque Nuance il y a des animaux verts/gris verts... ce n'est pas precise dans le sujet
SELECT idani AS "Numero", noman AS "Nom", poids AS "Poids"
FROM animal
WHERE coule LIKE '%Vert%' AND poids > 0.3;

-- Req n°13
SELECT idani AS "Numero", noman AS "Nom", poids AS "Poids"
FROM animal
WHERE coule LIKE '%Vert%' OR poids > 0.3;

-- Req n°14
SELECT idani AS "Numero", noman AS "Nom", poids AS "Poids"
FROM animal
WHERE coule NOT LIKE '%Vert%' AND poids <= 0.3;

-- Alternative
-- SELECT idani AS "Numero", noman AS "Nom", poids AS "Poids"
-- FROM animal
-- WHERE NOT (coule LIKE '%Vert%' OR poids > 0.3);

-- Req n°15
SELECT a.idani AS "Numero", a.noman AS "Nom", a.poids AS "Poids", c.nomcl AS "Nom proprietaire"
FROM animal AS a, client AS c
WHERE a.numcl = c.numcl AND a.coule LIKE '%Vert%'
ORDER BY a.poids;

-- Req n°16
SELECT a.idani AS "Numero", a.noman AS "Nom", a.daten AS "Date naissance", c.nomcl AS "Nom proprietaire", c.clidep AS "Client depuis"
FROM animal AS a, client AS c
WHERE a.numcl = c.numcl AND a.daten > c.clidep;

-- Req n°17
SELECT a.idani AS "Numero", a.noman AS "Nom", v.numvi AS "Numero Visite", v.datev AS "Date de Visite"
FROM animal AS a
LEFT OUTER JOIN visite AS v
ON v.idani = a.idani
WHERE a.noman LIKE 'P%';

-- Req n°18
SELECT a.idani AS "Numero", a.noman AS "Nom"
FROM animal AS a
LEFT OUTER JOIN visite AS v
ON v.idani = a.idani
WHERE a.noman LIKE 'P%' AND v.numvi IS NULL;


-- Req n°19
SELECT a1.idani AS "Numero", a1.noman AS "Nom", a1.poids AS "Poids"
FROM animal AS a1, animal AS a2
WHERE a1.poids > a2.poids AND a2.noman='Jake'
ORDER BY a1.poids;

-- Req n°20
SELECT DISTINCT a.idani AS "Numero", a.noman AS "Nom"
FROM animal AS a
     INNER JOIN visite AS v ON v.idani = a.idani
     INNER JOIN detail_visite AS dv ON dv.numvi = v.numvi
     INNER JOIN traitement AS t ON t.cotra = dv.cotra
     INNER JOIN medicament AS m ON m.comed = dv.comed
WHERE t.trait = 'Amputation d''un membre' OR m.medic = 'Byoactocaine - 100g';

--
-- Ensembliste
--


-- Req n°1
SELECT idani AS "Numero", noman AS "Nom", coule AS "Indicateur"
FROM animal
WHERE coule LIKE '%Brun%'
UNION
SELECT a.idani AS "Numero", a.noman AS "Nom", t.trait AS "Indicateur"
FROM animal AS a
     INNER JOIN visite AS v ON v.idani = a.idani
     INNER JOIN detail_visite AS dv ON dv.numvi = v.numvi
     INNER JOIN traitement AS t ON t.cotra = dv.cotra
WHERE t.trait = 'Examen respiratoire';

-- Req n°2
SELECT idani AS "Numero", noman AS "Nom"
FROM animal
WHERE coule LIKE '%Brun%'
INTERSECT
SELECT a.idani AS "Numero", a.noman AS "Nom"
FROM animal AS a
	INNER JOIN visite AS v ON v.idani = a.idani
	INNER JOIN detail_visite AS dv ON dv.numvi = v.numvi
	INNER JOIN traitement AS t ON t.cotra = dv.cotra
WHERE t.trait = 'Examen respiratoire';

-- Req n°3
SELECT idani AS "Numero", noman AS "Nom"
FROM animal
WHERE coule LIKE '%Brun%'
EXCEPT
SELECT a.idani AS "Numero", a.noman AS "Nom"
FROM animal AS a
	INNER JOIN visite AS v ON v.idani = a.idani
	INNER JOIN detail_visite AS dv ON dv.numvi = v.numvi
	INNER JOIN traitement AS t ON t.cotra = dv.cotra
WHERE t.trait = 'Examen respiratoire';


-- Req n°4
SELECT DISTINCT idani AS "Numero"
FROM animal
WHERE coule LIKE '%Brun%' OR coule LIKE '%Vert%'
INTERSECT
SELECT a.idani AS "Numero"
FROM animal AS a
	INNER JOIN visite AS v ON v.idani = a.idani;
-- Pas besoin d'utiliser SUM(v.numvi) >= 1, car si un animal est dans la table visite il en a eu au moins une d'après les contraintes des PK

-- Req n°5
SELECT DISTINCT a.idani AS "Numero"
FROM animal AS a
	INNER JOIN visite AS v ON v.idani = a.idani
WHERE coule LIKE '%Brun%' OR coule LIKE '%Vert%';
-- Pas besoin d'utiliser SUM(v.numvi) >= 1, car si un animal est dans la table visite il en a eu au moins une d'après les contraintes des PK

\o
