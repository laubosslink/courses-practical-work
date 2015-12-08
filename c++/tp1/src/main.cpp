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
 * @file main.cpp
 * 
 * Programme principale.
 */
#include <iostream>
#include "article.h"
using namespace std;

int main()
{
  /* Test de toutes les fonctions */
  /*    
	float clav;

	cout << "Vous allez entrer 4 nombres" << endl;

	clav = lire_clavier();
	cout << "fonction retourne le nombre lu: " << clav << endl;

	lire_clavier(&clav);
	cout << "fonction retourne l'argument passe par adresse: " << clav << endl;

	clav = resolve::lire_clavier(4);
	cout << "fonction retourne l'argument passe par valeur: " << clav << endl;

	lire_clavier(clav);
	cout << "fonction retourne l'argument passe par reference: " << clav << endl;

	std::cout << "Vous allez saisir un article" << std::endl;

	Article a = saisie_article();
	cout << "Article : " << a.designation << " avec le prix de " << a.prix << " euros." << endl;
*/
	cout << "Vous allez saisir 2 articles" << endl;

	Article l[2]; // taille = 2 
	saisie_articles(l, 2);

	cout << "Affichage des articles" << endl;

	affiche_articles(l, 2);

	blague(l, 2);

	cout << "Affichage des articles, apres l'echange des prix" << endl;

	affiche_articles(l, 2);

	blague_bis(l, 2);

	cout << "Affichage des articles, apres l'echange des prix (bis)" << endl;

	affiche_articles(l, 2);

	return 0;
}


