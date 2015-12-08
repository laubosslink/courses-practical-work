#include <iostream>

#include <math.h>
#include <string.h>

using namespace std;

#ifndef __MATRICE_H
#define __MATRICE_H

/**
 * Classe Matrice 
 */
class Matrice 
{
	private : 
	/**
	 * Attributs de la classe matrice 
	 */
	unsigned int nb_ligne, nb_colonne;
	double* coef;
	static int compteur;
	
	public :
	/**
	 * Constructeur par defaut de la classe Matrice
	 */
	Matrice();
	
	/**
	 * Constructeur à deux parametres
	 *@param nb_ligne : nombre de ligne de la matrice
	 *@param nb_colonne : nombre de colonne de la matrice
	 */
	Matrice (unsigned int nb_ligne, unsigned int nb_colonne);
	
	/**
	 * Destructeur de la classe Matrice
	 */
	~Matrice();
	
	/**
	 * Constructeur par recopie 
	 *@param M : reference constante sur une matrice
	 */
	Matrice (const Matrice & M);

	/**
	 * Constructeur par deplacement 
	 */
	Matrice ( Matrice && M);
	
	/**
	 * Operateur d'affectation par recopie
	 */
	Matrice & operator=(const Matrice & M);
	
	/**
	 * Operateur d'affectation par deplacement
	 */
	Matrice & operator=(Matrice && M);

/**
 * Méthodes et fonctions amies 
 */
 
	/**
	 * Surcharge de l'operateur +
	 *@param A : reference constante sur une Matrice
	 *@return Matrice : resultat de la somme des deux matrices
	 */
	Matrice operator+(const Matrice &A);
	
	/**
	 * Surcharge de l'operateur - 
	 *@param A : reference constance sur une Matrice
	 *@return Matrice : resultat de la difference des deux matrices
	 */
	Matrice operator-(const Matrice &A);
	
	/**
	 * Surcharge de l'operateur - unaire 
	 *@return Matrice : resultat de l'opération - unaire
	 */
	Matrice operator-();
	
	/**
	 * Surcharge de l'operateur [] 
	 *@param i : une ligne de la matrice
	 *@return un tableau des coefs de la ligne passee en param
	 */
	double* operator[](int i);
	
	/**
	 * Fonction amie : Operateur << 
	 * @param out : reference sur un ostream
	 * @param m : reference sur une matrice
	 * @return une reference sur un ostream
	 */
	friend ostream& operator<<(ostream &out, Matrice &m);
	/**
	 * Fonction amie : Operateur >>
	 * @param in : reference sur un instream
	 * @param m : reference sur une matrice
	 * @return une reference sur un instream
	 */
	friend istream& operator>>(istream &in, Matrice &m);
	
	/**
	 * Methode retournant la transposée d'une matrice
	 * @return une matrice
	 */
	Matrice transposer();
	
	/**
	 * Methode retournant une sous matrice d'une matrice
	 * @param i : une ligne de la matrice
	 * @param j : une colonne de la matrice
	 * @return une matrice
	 */
	Matrice sous_matrice(int i, int j);
	
	/**
	 * Methode retournant le determinant d'une matrice
	 * @return le determinant 
	 */
	double determinant();
	
	/**
	 * Methode retournant le cofacteur d'une matrice selon la ligne et la colonne passees en param
	 * @param i : ligne de la matrice
	 * @param j : colonne de la matrice
	 * @return le cofacteur 
	 */
	double cofacteur(int i, int j);
	
	/**
	 * Methode retournant la comatrice d'une matrice
	 *@return la comatrice 
	 */
	Matrice comatrice();
	
	/**
	 * Surcharge de l'operateur *
	 * @param x un double 
	 * @return matrice : resultat du produit d'une matrice avec un double
	 */
	Matrice operator*(double x);
	
	/**
	 * Methode retournant l'inverse d'une matrice
	 *@return matrice inverse
	 */
	Matrice inverse();
	
	/**
	 * getteur constant du nombre de ligne de la matrice
	 * @return le nombre de ligne
	 */
	double get_nb_ligne() const;
	
	/**
	 * getteur constant du nombre de colonne de la matrice
	 * @return le nombre de colonne
	 */
	double get_nb_colonne() const;
	
	/**
	 * getteur constant d'un coef
	 *@param i : ligne de la matrice
	 *@return le coef correspondant
	 */
	double get_coef(int i) const;
	
	/**
	 * Genere des valeurs aleatoire de la matrice
	 *@param value 
	 */
	void rand(int value);
	
	/**
	 * getteur du compteur 
	 *@return le compteur 
	 */
	int get_compteur();
	
	/**
	 * remise à zero du compteur 
	 */
	void reset_compteur();

};

#endif
