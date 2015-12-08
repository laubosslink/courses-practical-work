\o tp2.html
 \pset format html
 \pset border 1
 \pset title 'TP2'
 \pset tableattr align='center'

--Requête numero 1:
SELECT idani AS "Numero",noman AS "Nom",poids AS "poids"
FROM animal 
WHERE poids > (SELECT DISTINCT poids FROM animal WHERE noman = 'Jake')
ORDER BY poids;
--Cette méthode permet de recuperer une seule fois le poids de Jake comparé à la thétajointure qui elle necessite de comparer chaque animal avec tous les animaux jusqu'à trouver l'animal appellé 'Jake'

--Requête numero 2:
SELECT idani AS "Numero", noman AS "Nom"
FROM animal 
WHERE coule = (SELECT DISTINCT coule FROM animal WHERE noman = 'Mikos') 
AND poids >= (SELECT DISTINCT poids FROM animal WHERE noman = 'Jerry');

--Requête numero 3:
SELECT idani AS "Numero", noman AS "Nom"
FROM animal
WHERE poids > ALL (SELECT DISTINCT poids FROM animal WHERE coule='Gris');

--Requête numero 4:
SELECT idani AS "Numero", noman AS "Nom"
FROM animal
WHERE poids > ANY (SELECT DISTINCT poids FROM animal WHERE coule='Gris');

--Requête numero 5:
SELECT idani AS "Numero", noman AS "Nom"
FROM animal 
WHERE noman LIKE 'P%'
AND idani NOT IN (SELECT DISTINCT idani FROM visite);
-- Remarque d'ambiguité, il peut y avoir une date futur, dans ce cas il faut vérifier aussi si la date est supérieur à la date actuelle
--Cette methode recupère d'abord l'ensemble des idani se trouvant dans visite contrairement à la requete 18 du TP1 qui necessite de comparer l'idani de chaque animal avec les idani de ceux qui ont fait la visite

--Requête numero 6:
SELECT idani AS "Numero", noman AS "Nom"
FROM animal  
WHERE idani IN (
	SELECT idani 
	FROM visite 
	WHERE numvi IN (
		SELECT numvi 
		FROM detail_visite 
		WHERE cotra IN (
			SELECT cotra FROM traitement WHERE trait LIKE 'Amputation d''un membre' 
		) 
		AND comed IN (
			SELECT comed FROM medicament WHERE medic='Byactocaine - 100 g'
		)
	)
); 


--Expression Arithmetique : 
--Requête numero 1:
SELECT idani AS "Numero", SIGN(poids-taill) AS "Gros"
FROM animal;

--Requête numero 2: 
SELECT trait AS "Traitement", ROUND(prix*1.56, 2) AS "Prix en Euros"
FROM traitement;

--Requête numero 3:
SELECT medic AS "Medicament", prix * POW(2,12/5) AS "Prix"
FROM medicament ;

--Expressions sur chaines :
--Requête numero 4:
SELECT numcl AS "Numéro", LOWER(nomcl) AS "Nom", rue || ' ' || copos || ' ' || local AS "Adresse"
FROM client
WHERE typec = '1';

--Requête numero 5:
SELECT idani AS "Numero", noman AS "Animal", SUBSTR(coule, 1, 1) AS "Couleur"
FROM animal
WHERE coule = 'Vert' OR coule = 'Noir';

--Expressions sur dates :
--Requête numero 6:
SELECT 
	numvi AS "Numero de visite",
	datev AS "Date de visite",
	CURRENT_DATE-datev AS "Nbr jours",
	ROUND((CURRENT_DATE-datev)/31,0) AS "Nb mois",
	ROUND((CURRENT_DATE-datev)/365,0)  AS "Nb années"
FROM visite
WHERE datev IS NOT NULL;

--Requête numero 7:
SELECT CURRENT_DATE + interval '4 weeks' AS "Date dans 4 semaines";

--Requête numero 8:
SELECT idani AS "N° animal", noman AS "Nom animal", daten + interval '15 years' AS "Date de vaccination"
FROM animal
WHERE daten + interval '15 years' < current_date; 

-- equivalent : where current_date - daten > 365 * 15;

--Requête numero 9: 
SELECT numvi AS "Numero Visite", idani AS "Numero Animal" 
FROM visite
WHERE TO_CHAR(datev, 'YYYY-MM-DD') = '2001-02-18';

--Requête numero 10:
SELECT numcl AS "Numero Client", nomcl AS "Nom Client", local AS "Localite",
CASE
	WHEN typec='1' THEN 'Particulier'
	WHEN typec='2' THEN 'Entreprise privee'
	WHEN typec='3' THEN 'Etablissement public'
	END AS "Type Client"
FROM client;

--Requête numero 11:
SELECT 
	numvi AS "Numero de visite",
	idani AS "Numero animal",
	CASE
		WHEN dates=datep THEN 'Meme date'
		WHEN dates>datep THEN 'Date suivi'
		ELSE 'Date paiement'
	END AS "Plus grande",
	CASE
		WHEN dates>datep THEN dates
		ELSE datep
	END AS "Date"
FROM visite;

--Requête numero 12:
SELECT
	numvi AS "Numero de visite",
	idani AS "Numero animal",
	CASE WHEN dates IS NULL THEN 'Pas suivi' ELSE TO_CHAR(dates, 'YYYY-MM-DD') END AS "Date suivi"
FROM visite;

--Fonctions de groupe
--Requête numero 1:
SELECT ROUND(AVG(poids)::NUMERIC, 2) AS "Moyenne"
FROM animal;

--Requête numero 2.a : 
SELECT MIN(taill) AS "Taille minimale"
FROM animal;

--Requête numero 2.b : 
SELECT taill AS "Taille minimale", noman AS "Nom animal" 
FROM animal 
WHERE taill = (SELECT MIN(taill) FROM animal);

--Requête numero 3 : 
SELECT MAX(ABS(t.prix-m.prix)) AS "Marge maximum", ABS(MAX(t.prix)-MAX(m.prix)) AS "Difference"
FROM traitement AS t, medicament AS m, detail_visite AS dv
WHERE dv.comed = m.comed AND t.cotra = dv.cotra;

--Requête numero 4:
SELECT COUNT(idani) AS "Nombre animaux decedes"
FROM animal
WHERE deced='O';

--Requête numero 5:
SELECT COUNT(DISTINCT coule) AS "Nombre de couleur"
FROM animal;

--Requête numero 6:
SELECT coule AS "Couleur", ROUND(AVG(poids)::NUMERIC,2) AS "Poids moyen", COUNT(idani) AS "Nombre animaux"
FROM animal 
GROUP BY coule
ORDER BY COUNT(idani) DESC;

--Requête numero 7: 
SELECT coule AS "Couleur", ROUND(AVG(poids)::NUMERIC,2) AS "Poids moyen", COUNT(idani) AS "Nombre animaux"
FROM animal 
WHERE steril <> 'O'
GROUP BY coule
ORDER BY COUNT(idani) DESC;

--Requête numero 8: 
SELECT 
	coule AS "Couleur", 
	ROUND(AVG(poids)::NUMERIC,2) AS "Poids moyen", 
    COUNT(idani) AS "Nombre animaux"
FROM animal 
WHERE steril <> 'O'
GROUP BY coule
HAVING COUNT(idani) > 5
ORDER BY COUNT(idani) DESC;

--Requête numero 9: 
SELECT idani AS "Numero animal", COUNT(numvi)
FROM visite 
WHERE TO_CHAR(datev, 'YYYY-MM-DD') BETWEEN '2001-01-01' AND '2001-05-31'
GROUP BY idani
HAVING COUNT(numvi) > 2;

--Requête numero 10:
SELECT 
	c.nomcl AS "Nom client", 
	COUNT(DISTINCT a.idani), 
	SUM(t.prix), SUM(COALESCE(m.prix,0)), 
	SUM(t.prix) + SUM(COALESCE(m.prix,0))
FROM client c
	INNER JOIN animal a ON a.numcl = c.numcl
	INNER JOIN visite v ON v.idani = a.idani
	INNER JOIN detail_visite dv ON dv.numvi = v.numvi
	INNER JOIN traitement t ON t.cotra = dv.cotra
	LEFT JOIN medicament m ON m.comed = dv.comed
WHERE DATE_PART('year',datev) = '2001'
GROUP BY c.nomcl,c.numcl
HAVING SUM(t.prix) + SUM(COALESCE(m.prix,0))>1000;

--Requête numero 11:
SELECT DISTINCT c.numcl AS "Numero client", c.nomcl AS "Nom client", c.codep AS "Departement", MAX(v.datev) AS "Derniere date"
FROM client c
        INNER JOIN animal a ON a.numcl = c.numcl
        INNER JOIN visite v ON v.idani = a.idani
GROUP BY c.numcl;

--Requête numero 12:
SELECT idani AS "Numero animal", datev AS "Date de visite"
FROM visite
WHERE idani IN (
	SELECT v.idani
	FROM animal a
		INNER JOIN visite v ON v.idani = a.idani
	WHERE a.coule = 'Vert' OR a.coule = 'Gris'
	GROUP BY v.idani
	HAVING COUNT(v.numvi) = 2
);

--Requête numero 13:



\o
