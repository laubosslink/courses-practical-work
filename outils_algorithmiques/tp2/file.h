/**
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 * 
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written premission of the authors
 */
 
/**
 * @author ELHIMDI Yasmine <yasmine.elhimdi@ecole.ensicaen.fr>
 * @author PARMENTIER Laurent <laurent.parmentier@ecole.ensicaen.fr, laubosslink@society-lbl.com>
 * @version 1.0 
 * @date 03-02-2013
 */
 
/** 
 * @file pile.h
 * 
 * Le fichier d'en tete de la Filo
 */

#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

typedef struct Node* Node;

typedef struct Filo* Filo;

#include "abr.h"

/**
 * Permet de creer une Filo
 * @return pointeur vers une structure Filo
 */
Filo makeFilo();

/**
 * Permet de verifier si la file est vide
 * @param f la pile Filo
 * @return 1 si elle est vide, 0 sinon
 */
int emptyFilo(Filo f);

/**
 * Permet d'ajouter un element dans la Filo
 * @param value la valeur a ajouter
 * @param f la Filo dans laquelle on ajoute l'element
 */
void addFiloElmt(NOEUD* value, Filo f);

/**
 * Permet de defiler un element dans la file
 * @param f la Filo
 */
void removeFiloElmt(Filo f);

/**
 * Permet de defiler un element dans la file
 * @param f la Filo
 * @return le noeud defile
 */
NOEUD* popFiloElmt(Filo f);

/**
 * Permet de concatener deux files
 * @param f1 la file a mettre en "tete"
 * @param f2 la file ajouter en "bout"
 */
void concatenate(Filo f1, Filo f2);

/**
 * Permet d'afficher une file
 * @param f Le pointeur de la file
 * @see Filo
 */
void showFilo(Filo f);

#endif
