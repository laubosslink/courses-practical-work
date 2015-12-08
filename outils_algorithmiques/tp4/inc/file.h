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
 * @file file.h
 *
 * Le fichier d'en tete de la FIFO
 */

#ifndef INCLUDED_H_FILE
#define INCLUDED_H_FILE

typedef struct Node* Node;

typedef struct Fifo* Fifo;

/**
 * Permet de creer une FIFO
 * @return pointeur vers une structure FIFO
 */
Fifo makeFifo();

/**
 * Permet de verifier si la file est vide
 * @param f la pile FIFO
 * @return 1 si elle est vide, 0 sinon
 */
int emptyFifo(Fifo f);

/**
 * Permet d'ajouter un element dans la FIFO
 * @param value la valeur a ajouter
 * @param f la fifo dans laquelle on ajoute l'element
 */
void addFifoElmt(int value, Fifo f);

/**
 * Permet de retirer un element dans la file
 * @param f la fifo
 */
void removeFifoElmt(Fifo f);

/**
 * Permet de defiler un element dans la file
 * @param f la fifo
 * @see emptyFifo(Fifo f)
 * @return l'entier à défiler (-1 si la file est vide, vérifier avec emptyFifo)
 */
int popFifoElmt(Fifo f);

/**
 * Permet de concatener deux files
 * @param f1 la file a mettre en "tete"
 * @param f2 la file ajouter en "bout"
 */
void concatenate(Fifo f1, Fifo f2);

/**
 * Permet d'afficher une file
 * @param f Le pointeur de la file
 * @see Fifo
 */
void showFifo(Fifo f);

/**
 * Permet de detruire la file
 * @param f la file
 */
void destruction(Fifo f);

#endif
