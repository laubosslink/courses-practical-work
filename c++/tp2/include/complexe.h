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
 * @version 1.2
 * @date 10-10-2014
 */

/**
 * @file complexe.h
 *
 * Le fichier header du programme complexe.
 */

#ifndef COMPLEXE_H
#define COMPLEXE_H

using namespace std;

class Complexe
{
	private:

	float reel, imaginaire;

	public:

	/**
	 * Constructeur par defaut
	 */
	//Complexe();

  /**
	 * Constructeur à deux arguments
	 *@param float reel ayant 0.0 comme valeur par defaut
	 *@param float imaginaire ayant 0.0 comme valeur par defaut
	 */
	Complexe(float reel = 0.0, float imaginaire = 0.0);
	/**
	 * Constructeur par recopie
	 *@param une reference constante a un Complexe
	 */
	Complexe(const Complexe & c);

	/**
	 * Operateur d'affectation
	 * @param une reference constante a un Complexe
	 */
	Complexe & operator=(const Complexe & c);

	/**
	 * Fonction getteur retournant la partie réelle du complexe
	 * @return la partie reel
	 */
	float get_reel() const
	{
		return reel;
	}

	/**
	 * Fonction getteur retournant la partie imaginaire du complexe
	 * @return la partie imaginaire
	 */
	float get_imaginaire() const
	{
		return imaginaire;
	}

	/**
	 * Fonction getteur retournant le module du complexe
	 * @return le module
	 */
	float get_module() const;

	/**
	 * Fonction getteur retournant l'argument du complexe
	 * @return l'argument
	 */
	float get_argument() const;

	/**
	 * Fonction permettant l'affichage du complexe
	 */
	void affiche_complexe();

	/**
	 * Fonction permettant de permuter la partie reel avec la partie imaginaire
	 */
	void swap();

};

/**
 * Fonction sommant deux complexes
 * @param const Complexe &a : reference constante sur un complexe
 * @param const Complexe &b : refence constante sur un complexe
 * @return Complexe : le resultat de la somme des deux complexe
 */
Complexe somme (const Complexe &a, const Complexe &b);

/**
 * Fonction faisant la difference de deux complexes
 * @param const Complexe &a : reference constante sur un complexe
 * @param const Complexe &b : refence constante sur un complexe
 * @return Complexe : le resultat de la difference des deux complexe
 */
Complexe difference(const Complexe &a, const Complexe &b);

/**
 * Fonction faisant le produit de deux complexes
 * @param const Complexe &a : reference constante sur un complexe
 * @param const Complexe &b : refence constante sur un complexe
 * @return Complexe : le resultat du produit des deux complexe
 */
Complexe produit(const Complexe &a, const Complexe &b);

/**
 * Surcharge de la fonction somme
 * @param const Complexe &a : reference constante sur un complexe
 * @param const Complexe &b : refence constante sur un complexe
 * @return Complexe : le resultat de la somme des deux complexe
 */
Complexe operator+(const Complexe &a, const Complexe &b);

/**
 * Surcharge de la fonction difference
 * @param const Complexe &a : reference constante sur un complexe
 * @param const Complexe &b : refence constante sur un complexe
 * @return Complexe : le resultat de la somme des deux complexe
 */
Complexe operator-(const Complexe &a, const Complexe &b);

/**
 * Surcharge de la fonction produit
 * @param const Complexe &a : reference constante sur un complexe
 * @param const Complexe &b : refence constante sur un complexe
 * @return Complexe : le resultat de la somme des deux complexe
 */
Complexe operator*(const Complexe &a, const Complexe &b);

/**
 * Fonction retournant le module à 1 d'un complexe
 * @param Complexe z
 * @return Complexe : un complexe normalisé
 */
Complexe normalise(Complexe z);

/**
 * Fonction faisant une rotation d'angle rot du complexe z
 * @param Complexe &z : reference sur un complexe
 * @param rot : angle de rotation
 * @return Complexe transformé par une rotation
 */
Complexe rotation(Complexe & z, float rot);

/**
 * Fonction retournant le complexe ayant le plus grand module
 * @param Complexe z1
 * @param Complexe z2
 * @return Complexe dont le module est le plus grand
 */
Complexe & plus_grand(Complexe z1, Complexe z2);

/**
 * Fonction qui calcule les racine n-ième de l'unité
 * @param n
 * @param tableau de complexe
 */
void racine_unite(int n, Complexe tab[]);


#endif
