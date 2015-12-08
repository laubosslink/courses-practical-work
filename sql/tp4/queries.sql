\o tp4.html
\pset title 'TP 4 ELHIMDI PARMENTIER'

\pset format html
\pset border 1
\pset tableattr align='center'


  -- I) Creation et suppresion de tables

DROP TABLE IF EXISTS parmentier.type_animal CASCADE;

CREATE TABLE type_animal
(
  cotypa CHAR(2),
  typea VARCHAR(20) NOT NULL,
  
  CONSTRAINT type_animal_cotypa_pk PRIMARY KEY (cotypa),
  
  CONSTRAINT type_animal_typea CHECK(typea = UPPER(typea))
);

\d parmentier.type_animal
\d public.type_animal

DROP TABLE IF EXISTS parmentier.departement CASCADE;

CREATE TABLE departement
(
  codep CHAR(2),
  depar VARCHAR(20) NOT NULL,
  tauta NUMERIC(5,3) DEFAULT 0,
  
  CONSTRAINT departement_codep_pk PRIMARY KEY(codep),
  
  CONSTRAINT departement_codep CHECK(TO_NUMBER(codep,'99') BETWEEN 01 AND 95 OR codep = '99'),
  CONSTRAINT departement_tauta CHECK(tauta BETWEEN 0 AND 1)
);

\d parmentier.departement
\d public.departement

DROP TABLE IF EXISTS parmentier.client CASCADE;

CREATE TABLE client
(
  numcl CHAR(5),
  codep CHAR(2) NOT NULL ,
  typec CHAR(1) NOT NULL,
  nomcl VARCHAR(30) NOT NULL,
  rue VARCHAR(35) NOT NULL,
  local VARCHAR(30) NOT NULL,
  copos CHAR(5) NOT NULL,
  telep CHAR(10) DEFAULT NULL,
  clidep DATE DEFAULT NULL,
  remis NUMERIC(5,3) DEFAULT 0,
  
  CONSTRAINT client_numcl_pk PRIMARY KEY(numcl),
  CONSTRAINT client_codep_fk FOREIGN KEY(codep) REFERENCES parmentier.departement(codep),
  
  CONSTRAINT client_numcl CHECK(substr(numcl,1,2) BETWEEN 'AA' AND 'ZZ' AND TO_NUMBER(substr(numcl,3,5),'999') BETWEEN 000 AND 999),
  CONSTRAINT client_type CHECK(typec IN ('1','2','3')),
  CONSTRAINT client_copos CHECK(substr(copos,1,2) = codep),
  CONSTRAINT client_remis CHECK(remis BETWEEN 0 AND 1)
);

\d parmentier.client
\d public.client


DROP TABLE IF EXISTS parmentier.animal CASCADE;

CREATE TABLE animal
(
  idani CHAR(8) NOT NULL,
  numcl CHAR(5) DEFAULT NULL,
  cotypa CHAR(2) NOT NULL ,
  noman VARCHAR(20) DEFAULT NULL,
  race VARCHAR(20) DEFAULT NULL,
  daten DATE DEFAULT NULL,
  sexe CHAR(1) NOT NULL,
  coule VARCHAR(20) NOT NULL,
  steril CHAR(1) DEFAULT 'N',
  taill FLOAT NOT NULL,
  poids FLOAT NOT NULL,
  deced CHAR(1) DEFAULT 'N',
  comme VARCHAR(250) DEFAULT NULL,
  
  CONSTRAINT animal_idani_pk PRIMARY KEY(idani),
  CONSTRAINT animal_numcl_fk FOREIGN KEY(numcl) REFERENCES parmentier.client(numcl),
  CONSTRAINT animal_cotypa_fk FOREIGN KEY(cotypa) REFERENCES parmentier.type_animal(cotypa),
  
  CONSTRAINT animal_sexe CHECK(sexe IN ('M','F','I')),
  CONSTRAINT animal_steril CHECK(steril IN ('O','N')),
  CONSTRAINT animal_taill CHECK(taill BETWEEN 1 AND 300),
  CONSTRAINT animal_poids CHECK(poids BETWEEN 0 AND 1500),
  CONSTRAINT animal_deced CHECK(deced IN ('O','N'))
);

\d parmentier.animal
\d public.animal

INSERT INTO parmentier.type_animal
VALUES('1','CHIEN');

INSERT INTO parmentier.departement
VALUES('67','HAUT-RHIN','0.1');

INSERT INTO parmentier.client
VALUES('BC041','67','1','Quentin','rue des pucelles','STRASBOURG','67000','0101010101',NULL,'0.5');

INSERT INTO parmentier.animal
VALUES('00000001','BC041','1',NULL,NULL,NULL,'M','noir','N',32,52,'N',NULL);

\qecho '<h1>Table type_animal</h1>'
\pset tableattr align='center'
SELECT * FROM parmentier.type_animal;

\qecho '<h1>Table departement</h1>'
\pset tableattr align='center'
SELECT * FROM parmentier.departement;

\qecho '<h1>Table Client</h1>'
\pset tableattr align='center'
SELECT * FROM parmentier.client;

\qecho '<h1>Table Animal</h1>'
\pset tableattr align='center'
SELECT * FROM parmentier.animal;

-- II) Creation et suppression d'indexes

\qecho '<h1>Les differents index</h1>'
\pset tableattr align='center'
SELECT * FROM PG_INDEXES;

CREATE INDEX numcl_ind ON parmentier.animal(numcl);
CREATE INDEX cotypa_ind ON parmentier.animal(cotypa);
CREATE INDEX codep_index ON parmentier.client(codep);

-- l'index des clés étrangères permet l'execution plus rapide des jointures

CREATE INDEX nomcl_ind ON parmentier.client(nomcl);

DROP TABLE IF EXISTS parmentier.visite CASCADE;
CREATE TABLE visite
(
  numvi CHAR(10),
  idani CHAR(8) NOT NULL,
  datev DATE DEFAULT CURRENT_DATE,
  types VARCHAR(11) DEFAULT NULL,
  dates DATE,
  typep VARCHAR(10),
  datep DATE DEFAULT NULL,
  monpa NUMERIC(8,2) DEFAULT 0,
  taxab CHAR(1) DEFAULT 'N',
  detai VARCHAR(50) DEFAULT NULL,
  
  CONSTRAINT visite_numvi_pk PRIMARY KEY(numvi),
  CONSTRAINT visite_idani_fk FOREIGN KEY(idani) REFERENCES parmentier.animal(idani),
  
  CONSTRAINT visite_date_check CHECK(dates > datev),
  CONSTRAINT visite_typep_check CHECK(typep IN ('Liquide','Cheque','Traite','Compte','Gratuit')),
  CONSTRAINT visite_monpa_ceck CHECK(monpa >= 0),
  CONSTRAINT visite_taxav_check CHECK(taxab IN ('O','N'))
);

\d parmentier.visite
\d public.visite

CREATE INDEX datev_ind ON parmentier.visite(datev DESC, idani ASC);

-- index pour la requete avec where sur la daten et le poids
CREATE INDEX aide_ind ON parmentier.animal(daten, poids);

--III) Accord et retrait de privilège

--Privilège de lecture de la table client

GRANT SELECT ON parmentier.client
TO public,mauranyapin,elhimdi ;

REVOKE SELECT ON parmentier.client
FROM public;

--Privilège d'insertion dans la table client

GRANT INSERT ON parmentier.client
TO elhimdi;

REVOKE INSERT ON parmentier.client
FROM elhimdi;


--Privilège de modification de la table animal

GRANT UPDATE ON parmentier.animal
TO elhimdi;

REVOKE UPDATE ON parmentier.animal
FROM elhimdi;


--Privilège de référence sur la table traitement

DROP TABLE IF EXISTS parmentier.traitement CASCADE;

CREATE TABLE parmentier.traitement
(
  cotra CHAR(4),
  trait VARCHAR(30)  NOT NULL,
  prix NUMERIC(8,2)  NOT NULL,
  
  CONSTRAINT traitement_cotra_pk PRIMARY KEY(cotra),
  
  CONSTRAINT traitement_prix_check CHECK(prix >= 0)
);

\d parmentier.traitement
\d public.traitement

GRANT REFERENCES ON parmentier.traitement
TO elhimdi;

REVOKE REFERENCES ON parmentier.traitement
FROM elhimdi;

--Privilège de lecture de la table client en cascade

GRANT SELECT ON parmentier.client
TO elhimdi WITH GRANT OPTION;

REVOKE SELECT ON parmentier.client
FROM elhimdi CASCADE;

--Reprise de tous les privilèges

REVOKE ALL PRIVILEGES ON parmentier.client, parmentier.traitement, parmentier.animal
FROM public, elhimdi, parmentier CASCADE;

-- IV) Chargement des tables

DELETE FROM parmenter.visite;
DELETE FROM parmenter.animal;
DELETE FROM parmentier.client;
DELETE FROM parmentier.traitement;
DELETE FROM parmentier.type_animal;
DELETE FROM parmentier.departement;

\i departement.sql
\i type_animal.sql

ALTER TABLE parmentier.client ADD COLUMN photofichier VARCHAR(10);
ALTER TABLE parmentier.client ADD COLUMN photo BYTEA;

\i client.sql

ALTER TABLE parmentier.animal ADD COLUMN photofichier VARCHAR(17);
ALTER TABLE parmentier.animal ADD COLUMN photo BYTEA;

\i animal.sql

\i visite.sql

\i traitement.sql

DROP TABLE IF EXISTS parmentier.medicament CASCADE;

CREATE TABLE parmentier.medicament
(
  comed CHAR(4),
  trait VARCHAR(30)  NOT NULL,
  prix NUMERIC(8,2)  NOT NULL,
  
  CONSTRAINT medicament_comed_pk PRIMARY KEY(comed),
  
  CONSTRAINT medicament_prix_check CHECK(prix >= 0)
);

\i medicament.sql

DROP TABLE IF EXISTS parmentier.detail_visite CASCADE;

CREATE TABLE parmentier.detail_visite
(
  numvi CHAR(10),
  numli CHAR(3),
  comed CHAR(4),
  cotra CHAR(4) NOT NULL,
  typev VARCHAR(20),
  
  CONSTRAINT detail_visite_numvi_pk PRIMARY KEY(numvi, numli),
  
  CONSTRAINT detail_visite_cotra_fk FOREIGN KEY (cotra) REFERENCES parmentier.traitement(cotra),
  CONSTRAINT detail_visite_comed_fk FOREIGN KEY (comed) REFERENCES parmentier.medicament(comed),
  
  CONSTRAINT detail_visite_typev_check CHECK(typev IN ('AUTRE','BLESSURE','HOSPITALISATION','PHYSIQUE','MALADIE', 'ROUTINE', 'TOILETTAGE'))
);

\i detail_visite.sql

-- V) Sauvegarde, restauration (sous POSTGRES)

-- Export
pg_dump -F -c -h postgres -U parmentier -n parmentier clinique > clinique.tar

-- on détruit la table
DROP TABLE detail_visite;
  
-- Import de la table detail_visite
pg_restore -d clinique -t detail_visite -U parmentier -h postgres clinique.tar

\o
