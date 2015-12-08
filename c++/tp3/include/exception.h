#include <iostream>

using namespace std;

#ifndef __EXCEPTION_H
#define __EXCEPTION_H
/**
 * Classe Erreur pour les gestions d'exceptions. 
 * Herite de la class exception de la librairie standard
 */
class Erreur : public exception 
{
private : 
	const char* message;
	
public:
	/**
	 * Constructeur
	 */
	Erreur(const char* message);
	
	/**
	 * Methode retournant le message d'erreur
	 */
	const char* what() const throw();
	
};

/**
 * Classe ErreurTaille pour les gestions d'exceptions concernant la taille d'une matrice
 * Herite de la class Erreur
 */
class ErreurTaille : public Erreur 
{
public :
	ErreurTaille();
};

/**
 * Classe ErreurDepassement pour les gestions d'exceptions concernant le dépassement d'indice  
 * Herite de la class Erreur
 */
class ErreurDepassement : public Erreur
{
public : 
	ErreurDepassement();
};

/**
 * Classe ErreurMatriceCarre pour les gestions d'exceptions des matrices non carrés   
 * Herite de la class Erreur
 */
class ErreurMatriceCarre : public Erreur
{
public : 
	ErreurMatriceCarre();
};

/**
 * Classe ErreurDeterminant pour les gestions d'exceptions concernant l'opération determinant  
 * Herite de la class Erreur
 */
class ErreurDeterminant : public Erreur
{
public : 
	ErreurDeterminant();
};

#endif
