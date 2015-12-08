#ifndef ABR_H_INCLUDED
#define ABR_H_INCLUDED

typedef int element;

typedef struct noeud NOEUD;

typedef struct noeud *ABR;

#include "file.h"

/**
 * Permet de creer un arbre vide
 * @return un pointeur sur un noeud
 */
NOEUD *arbre_vide();

element arbre_get_element(NOEUD *p);

/**
 * Permer d'inserer un noeud dans un arbre
 * @param p le noeud dans lequel on insere l'arbre
 * @param x l'element a inserer
 */
NOEUD *insere(NOEUD *p, element x);

/**
 * Permet d'afficher les prefixe d'un arbre
 * @param p l'arbre
 */
void parcour_RGD(NOEUD *p);


/**
 * Permet d'afficher les suffixe d'un arbre
 * @param p l'arbre
 */
void parcour_GDR(NOEUD *p);


/**
 * Permet d'afficher les infixe d'un arbre
 * @param p l'arbre
 */
void parcour_GRD(NOEUD *p);


/**
 * Permet d'afficher les prefixe/suffixe, et de compter les noeuds d'un arbre
 * @param p l'arbre
 */
int compter_RGD_GDR(NOEUD *p);


/**
 * Permet de parcourir un arbre en largeur
 * @param p l'arbre
 */
void parcour_largeur(NOEUD *p);

/**
 * Permet de recuperer la bordure d'un arbre
 * @param p l'arbre
 * @return la pile contenant les noeuds qui se trouvent sur la bordure de l'arbre
 */
Filo bordure(NOEUD *p);

/**
 * Permet d'afficher un arbre
 * @param p l'arbre
 * @param col le nombre de colonne
 */
void affiche_arbre(NOEUD *p, int col);

#endif
