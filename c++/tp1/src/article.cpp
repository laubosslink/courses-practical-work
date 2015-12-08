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
 * @version 1.1 
 * @date 25-09-2014
 */
/** 
 * @file article-1.cpp
 * 
 * Le fichier contenant l'implémentation de toutes les fonctions.
 */

#include <iostream>
#include "article.h"


// 2.2.1 validation de saisie

float lire_clavier()
{
  float x;
  cin >> x;
  while(x <= 0) cin >> x;
  return x;
}


void lire_clavier(float *x)
{
  cin >> *x;
  while(*x <= 0) cin >> *x;
}

namespace resolve {
  float lire_clavier(float x)
  {
    cin >> x;
    while(x <= 0) cin >> x;
    return x;
  }
}

void lire_clavier(float &x)
{
  cin >> x;
  while(x <= 0) cin >> x;
}

// 2.2.2 saisie d'article

Article saisie_article()
{
  Article a;
  cout << "Designation article:" << endl;
  cin >> a.designation;
  cout << "Prix article:" << endl;
  cin >> a.prix;
  while(a.prix <= 0) cin >> a.prix;
  return a;
}

// 2.2.3 saisie d'une liste d'articles

void saisie_articles(Article a[], int taille)
{
  for(int i=0; i<taille; i++)
    {
      a[i] = saisie_article();
    }
}

// 2.3 affichage article(s)
void affiche_article(Article a)
{
  cout << "Article : " << a.designation << " avec le prix de " << a.prix << " euros." << endl;
}

void affiche_articles(Article a[], int taille)
{
  for(int i=0; i<taille; i++)
    affiche_article(a[i]);
}


// 2.4.1 echange
void echange_prix(Article &a1, Article &a2)
{
  int tmp = a1.prix;
  a1.prix = a2.prix;
  a2.prix = tmp;
}

// 2.4.2 Prix min/max
Article &article_moins_cher(Article a[], int taille)
{
  Article *amc = a; // Passage par pointeur pour pouvoir modifier la valeur de l'article passé en param
  
  for(int i=1; i<taille; i++)
    {
      if (a[i].prix < amc->prix)
	{
	  amc = a+i;
	}
    }
  
  Article &r = *amc;
  return r;
}

Article &article_plus_cher(Article a[], int taille)
{  
  Article *apc = a;
  
  for(int i=1; i<taille; i++)
    {
      if (a[i].prix > apc->prix)
	{
	  apc = a+i;
	}
    }
  
  Article &r = *apc;
  return r;
}

// 2.4.3 Blague
void blague(Article a[], int taille)
{
  echange_prix(article_plus_cher(a, taille), article_moins_cher(a, taille)); //fonction implémentée en une seule instruction
}

// 2.4.4 Blague bis
void blague_bis(Article a[], int taille)
{
  Article &moins_cher = article_moins_cher(a, taille);
  Article &plus_cher = article_plus_cher(a, taille);
  echange_prix(moins_cher, plus_cher);
}


