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
 * @author PARMENTIER Laurent <parmentier@ecole.ensicaen.fr, laubosslink@society-lbl.com>
 * @author EL HIMDI Yasmine <yasmine.elhimdi@ecole.ensicaen.fr>
 * @version 1.0 
 * @date 03-02-2013
 */
 
/** 
 * @file abr.h
 * 
 * Les fonctions permettant de manipuler l'arbre
 */
 
#ifndef ABR_H_INCLUDED 
#define ABR_H_INCLUDED

typedef char element;
typedef struct noeud *NOEUD;

/**
 * Permet de créer un arbre vide
 * @return un arbre qui contient la valeur '\0'
 */
NOEUD creer_arbre();

/**
 * Permet de rechercher un élément dans un arbre
 * @param n le premier noeud de l'arbre
 * @param str l'élément
 * @return 1 si l'élément est présent, 0 sinon
 */
int recherche_element(NOEUD n, char* str);

/**
 * Permet d'insérer un élément dans l'arbre
 * @param n le noeud dans lequel on veut insérer l'élément
 * @param str l'élément a insérer
 * @return le noeud n entree avec l'element insere
 */
NOEUD insertion_element(NOEUD n, char* str);

/**
 * Permet d'utiliser la recursivite pour l'insertion
 * @see insertion_element
 * @param n le noeud dans lequel on veut insérer l'élément
 * @param str l'élément a insérer
 */
void insertion_element_rec(NOEUD n, char* str);

/**
 * Permet de charger un fichier contenant des mots dans un arbre
 * @param f le fichier
 * @return l'arbre
 */
NOEUD chargement(FILE *f);

/**
 * Permet d'afficher un arbre 
 * @param n le noeud
 */
void afficher_arbre(NOEUD n, int col);

#if DEBUG_AFFICHE == 1
/**
 * Permet de faire un debug sur le nombre d'appel récursif
 */
void show_debug_n_appel();
#endif

#endif
