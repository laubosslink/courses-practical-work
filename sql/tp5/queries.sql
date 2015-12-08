-- Exercice 1

-- Création de la table

DROP TABLE IF EXISTS parmentier.tp5_exo1 CASCADE;

CREATE TABLE tp5_exo1(
  i INTEGER,
  parite CHAR(10),
  icarre INTEGER,
  icube INTEGER,
  
  CONSTRAINT tp5_exo1_check CHECK(parite IN ('pair','impair'))
);

-- Création de la fonction
CREATE OR REPLACE FUNCTION ex1() RETURNS void AS $$
  DECLARE
  i INT:=1;
  parite VARCHAR;
  
  BEGIN
    WHILE i <= 10
    LOOP
      IF MOD(i,2) = 0
      THEN
        parite := 'pair';
      ELSE
        parite := 'impair';
      END IF;
      
      INSERT INTO tp5_exo1 VALUES(i, parite, i*i, i*i*i);
      i := i + 1;
    END LOOP;
    
    FOR i IN 1 .. 10
    LOOP
      IF MOD(i,2) = 0
      THEN
        parite := 'pair';
      ELSE
        parite := 'impair';
      END IF;
      
      INSERT INTO tp5_exo1 VALUES(i, parite, i*i, i*i*i);
    END LOOP;
  END;
$$ LANGUAGE plpgsql;

-- Exercice 2 
CREATE OR REPLACE FUNCTION ex2(client.numcl%type) RETURNS client AS $$
  DECLARE
    clrow client%ROWTYPE;  -- %ROWTYPE facultatif
    num ALIAS FOR $1;
  
  BEGIN
    IF(SUBSTR(num,1,2) NOT BETWEEN 'AA' AND 'ZZ') OR (TO_NUMBER(substr(num,3,3),'999') NOT BETWEEN 000 AND 999)
    THEN
      RAISE EXCEPTION 'Le numero %, n''pas sous la forme AA9999', num;
    END IF;
  
    SELECT * INTO clrow FROM client WHERE client.numcl=num;
    
    IF NOT FOUND
    THEN
      RAISE EXCEPTION 'Le numero %, est hors domaine', num;
    ELSE
      RETURN clrow;
    END IF;
    
  END;
$$ LANGUAGE plpgsql;

-- Fonction plus légère
CREATE OR REPLACE FUNCTION ex2_light(client.numcl%type) RETURNS client AS $$
  DECLARE
    clrow client;
  BEGIN
    SELECT * INTO clrow FROM client WHERE client.numcl=$1;
    RETURN clrow;
  END;
$$ LANGUAGE plpgsql;

-- Exercice 3
CREATE OR REPLACE FUNCTION ex3(client.numcl%type) RETURNS RECORD AS $$ -- utilisation de RECORD lorsque retourne une ligne, et que certains champs (=> pas de *)
  DECLARE
  num ALIAS FOR $1;
  clrow RECORD; -- il faut utiliser RECORD et non %ROWTYPE !
  
  BEGIN
    SELECT nomcl as Nom, rue || ' ' || copos || ' ' || local AS Adresse INTO clrow FROM client WHERE client.numcl=num;
    
    IF NOT FOUND
    THEN
      RAISE EXCEPTION 'Pas de client numero %', num;
    ELSE
      RETURN clrow;
    END IF;
    
  END;
$$ LANGUAGE plpgsql;

-- Exercice 4 
DROP TABLE IF EXISTS parmentier.villes CASCADE;

CREATE TABLE villes AS SELECT DISTINCT local FROM client;

-- ajout d'une ville test (aucun client)
INSERT INTO villes VALUES('Caen');

-- création d'un type
DROP TYPE IF EXISTS infos_client CASCADE;
CREATE TYPE infos_client AS(nom text, adresse text);

-- Création de la fonction qui permet de récupérer les clients pour une localité
CREATE OR REPLACE FUNCTION ex4(client.local%type) RETURNS SETOF infos_client AS $$ -- SETOF implique RETURN NEXT
  DECLARE
  local_param ALIAS FOR $1;
  clrow infos_client;
  
  BEGIN
    
    -- plusieurs lignes, utilisation d'un FOR, et non INTO
    FOR clrow IN SELECT nomcl as Nom, rue || ' ' || copos || ' ' || local AS Adresse FROM client WHERE local=local_param
    LOOP
      RETURN NEXT clrow;
    END LOOP;
    RETURN;
  END;
$$ LANGUAGE plpgsql;

-- REMARQUE : il faut créer un type pour la fonction ci-dessus, on ne peut utiliser "RECORD" dans le RETURNS.
-- Ceci permet de faire par exemple : SELECT adresse FROM ex4('Le Lac');
-- Intérêt ? ca permet de selectionner que certains champs voulu

-- Création de la fonction qui liste les villes/clients
CREATE OR REPLACE FUNCTION ex4_app() RETURNS void AS $$
  DECLARE
  locrow RECORD;
  clrow RECORD;
-- nb INTEGER
  nbr RECORD;

  BEGIN
    FOR locrow IN SELECT local FROM villes
    LOOP
      RAISE NOTICE 'Ville de %', locrow.local;
      RAISE NOTICE '*************************';
      FOR clrow IN SELECT * FROM ex4(locrow.local)
      LOOP
        RAISE NOTICE '      Nom: %      Adresse: %', clrow.nom, clrow.adresse;
        -- nb := nb+1
      END LOOP;

      SELECT COUNT(*) AS nb INTO nbr FROM ex4(locrow.local); -- moins couteux, comme on a une boucle on pourrait aussi incrémenter un entier

      RAISE NOTICE '---> % clients', nbr.nb; -- RQ : on pourrait ommetre le .nb, et le "AS nb" dans le SELECT, car il n'y a qu'un seul champ
    END LOOP;
  END;
$$ LANGUAGE plpgsql;

-- Exercice 5

CREATE OR REPLACE FUNCTION ex5() RETURNS void AS $$
  DECLARE
  clrow RECORD;

  BEGIN
    FOR clrow IN SELECT numcl, nomcl, local, remis FROM client WHERE codep=(SELECT codep FROM departement WHERE depar='Gard')
    LOOP
      IF clrow.local = 'Nimes'
      THEN
        UPDATE client SET remis=remis*1.05 WHERE numcl=clrow.numcl;
        RAISE NOTICE 'La remise de % va etre augmentee', clrow.nomcl;
      ELSE
        RAISE NOTICE 'La remise de % va etre diminuee', clrow.nomcl;
      END IF;
    END LOOP;
  END;
$$ LANGUAGE plpgsql;

-- Exercice 6

-- Triger 1
CREATE OR REPLACE FUNCTION ex6_tr1() RETURNS TRIGGER AS $$
  DECLARE
    nb NUMERIC;
  BEGIN
    SELECT COUNT(numvi) INTO nb FROM visite;
    
    IF nb > 87
    THEN
      RAISE EXCEPTION 'Trop de visites en cours - desole';
    ELSE
      RETURN NEW;
    END IF;
  END;

$$ LANGUAGE plpgsql;

CREATE TRIGGER tr1 BEFORE INSERT ON visite
  FOR EACH ROW EXECUTE PROCEDURE ex6_tr1();

-- Triger 2
CREATE OR REPLACE FUNCTION ex6_tr2() RETURNS TRIGGER AS $$
  DECLARE
    deprow RECORD;
  BEGIN
    SELECT SUM(t.prix + COALESCE(m.prix,0)) AS somme
    INTO deprow
    FROM detail_visite dv
      LEFT JOIN medicament m ON m.comed = dv.comed
      JOIN traitement t ON t.cotra = dv.cotra
    WHERE dv.numvi = NEW.numvi;

    IF NEW.monpa <= deprow.somme
    THEN
      RETURN NEW;
    ELSE
      RAISE EXCEPTION 'Trop paye';
    END IF;
  END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tr2 BEFORE INSERT OR UPDATE ON visite
  FOR EACH ROW EXECUTE PROCEDURE ex6_tr2();

-- Triger 3

-- creation de la table hist_visite

DROP TABLE IF EXISTS parmentier.hist_visite CASCADE;

CREATE TABLE hist_visite AS SELECT *, CURRENT_DATE FROM public.visite LIMIT 0;

-- création du triger
CREATE OR REPLACE FUNCTION ex6_tr3() RETURNS TRIGGER AS $$
  DECLARE
  BEGIN
    INSERT INTO hist_visite VALUES(OLD.numvi, OLD.idani, OLD.datev, OLD.types, OLD.dates, OLD.typep, OLD.datep, OLD.monpa, OLD.taxab, OLD.detai, CURRENT_DATE);
    RETURN NEW;
  END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER tr3 BEFORE DELETE OR UPDATE ON visite
  FOR EACH ROW EXECUTE PROCEDURE ex6_tr3();
