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
 * @date 25-09-2014
 */
 
/** 
 * @file article.h
 * 
 * Le fichier header du programme articles de magasin.
 */

#ifndef ARTICLE_H
#define ARTICLE_H

using namespace std; 

struct Article {
  char designation[30];
  float prix;
};

/**
 * Lecture d'un nombre au clavier
 * @return le flottant lu au clavier
 */
float lire_clavier();

/**
 * Lecture d'un flottant au clavier, et modification par adresse
 * @param x pointeur du flottant à modifier
 */
void lire_clavier(float *x);

// Création d'un namespace qui répond au problème d'ambiguité avec la fonction lire_clavier(float &x)
namespace resolve {
  	/**
	 * Lecture d'un flottant au clavier, et retour de la valeur
	 * @param x la valeur passé en paramètre
	 * @return le flottant lu au clavier
	 */
  float lire_clavier(float x);
}

/**
 * Lecture d'un flottant au clavier
 * @param x référence d'un flottant
 */
void lire_clavier(float &x);

/**
 * Lecture d'un article
 * @return un article
 */
Article saisie_article();

/**
 * Lecture d'un tableau d'articles
 * @param a[] : un tableau d'article 
 * @param taille : la taille du tableau entré en parametre  
 */
void saisie_articles(Article a[], int taille);

/**
 * Affichage d'un article
 * @param a de type Article 
 */
void affiche_article(Article a);

/**
 * Affichage un tableau d'articles
 * @param a[]: tableau d'articles
 * @param taille : la taille du tableau d'articles passé en parametre
 */
void affiche_articles(Article a[], int taille);

/**
 * Echange le prix de deux Articles passés en parametre
 * @param &a1 : reference sur le premier article
 * @param &a2 : reference sur le deuxieme article
 */

void echange_prix(Article &a1, Article &a2);

/**
 * Retourne l'article le moins cher du tableau d'article passé en param
 *@param a[] : tableau d'articles
 *@param taille : la taille du tableau d'articles passé en parametre
 *@return une reference sur l'article
 */
Article &article_moins_cher(Article a[], int taille);

/**
 * Retourne l'article le plus cher du tableau d'article passé en param
 *@param a[] : tableau d'articles
 *@param taille : la taille du tableau d'articles passé en parametre
 *@return une reference sur l'article
 */
Article &article_plus_cher(Article a[], int taille);

/**
 * Echange les prix de l'article le plus cher et de l'article le moins cher
 * @param a[] : tableau d'articles
 * @param taille : la taille du tableau d'article passé en parametre
 */
void blague(Article a[], int taille);

/**
 * Autre methode pour l'echange les prix de l'article le plus cher et de l'article le moins cher
 * @param a[] : tableau d'articles
 * @param taille : la taille du tableau d'article passé en parametre
 */

void blague_bis(Article a[], int taille);

#endif
