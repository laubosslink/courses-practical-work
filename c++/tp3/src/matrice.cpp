/** 
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin 
 * F-14050 Caen Cedex 
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */ 

/**
 * @author El Himdi Yasmine <yasmine.elhimdi@ecole.ensicaen.fr> 
 * @author Parmentier Laurent <laurent.parmentier@ecole.ensicaen.fr> 
 * @version 1.2 - 23/11/2014
 */

/**
 * @file matrice.cpp
 * Implementation des méthodes/fonctions de la classe Matrice
 */

#include <iostream>

#include <math.h>
#include <string.h>

#include <matrice.h>
#include <exception.h>

using namespace std;

int Matrice::compteur = 0;

Matrice::Matrice()
{
	nb_ligne = nb_colonne = 0;
	coef = nullptr; 
}
	
Matrice::Matrice (unsigned int nb_ligne, unsigned int nb_colonne) 
{
	Matrice::nb_ligne = nb_ligne;
	Matrice::nb_colonne = nb_colonne;
	
	coef = new double[nb_colonne * nb_ligne];
}
	
Matrice::~Matrice()
{
	delete [] coef;
}
	
Matrice::Matrice(const Matrice & M)
{
	nb_ligne = M.nb_ligne;
	nb_colonne = M.nb_colonne;
			
	coef = new double [nb_ligne * nb_colonne];
	/*
	for(int i=0; i<nb_ligne * nb_colonne; i++)
		coef[i] = M.coef[i];
	*/
	memcpy(coef, M.coef, nb_ligne*nb_colonne*sizeof(double));
}

Matrice::Matrice(Matrice && M)
{
	/*
	cout << "Constructeur par deplacement " << endl; // Utile pour la trace d'excecution du constructeur par déplacement 
	*/
	
	nb_ligne = M.nb_ligne;
	nb_colonne = M.nb_colonne;
	coef = M.coef;
		
	M.nb_ligne = 0;
	M.nb_colonne = 0;
	M.coef = nullptr;
}
	
	
Matrice & Matrice::operator=(const Matrice & M)
{
	if(nb_ligne != M.nb_ligne || nb_colonne != M.nb_colonne){
		delete coef;
		coef = nullptr;
				
		nb_ligne = M.nb_ligne;
		nb_colonne = M.nb_colonne;
			
		coef = new double [nb_ligne * nb_colonne];
	}
	/*
	for(int i=0; i<nb_ligne * nb_colonne; i++)
		coef[i] = M.coef[i];
	*/
	memcpy(coef, M.coef, nb_ligne*nb_colonne*sizeof(double));
	return *this;
}
	
Matrice & Matrice::operator=(Matrice && M)
{
	/*
	cout << "Operateur d'affectation par déplacement " << endl;  //Utile pour la trace d'excecution de l'opérateur d'affectation par déplacement 
	*/
	delete coef;
	
	nb_ligne = M.nb_ligne;
	nb_colonne = M.nb_colonne;
	coef = M.coef;
		
	M.coef = nullptr;
	M.nb_ligne = 0;
	M.nb_colonne = 0;
}

/**
 * Méthodes et fonctions amies 
 */
Matrice Matrice::operator+(const Matrice &A)
{
		
	if(nb_ligne != A.nb_ligne || nb_colonne != A.nb_colonne){
		ErreurTaille et;
		throw et;
	}
		
	Matrice S (nb_ligne, nb_colonne);
			
	for( int i=0; i<nb_ligne * nb_colonne; i++)
		S.coef[i] = coef[i] + A.coef[i];
		
	return S;
}
	
Matrice Matrice::operator-(const Matrice &A)
{		
	if(nb_ligne != A.nb_ligne || nb_colonne != A.nb_colonne){
		ErreurTaille et;
		throw et;
	}
		
	Matrice D(nb_ligne, nb_colonne);
			
	for(int i=0; i<nb_ligne * nb_colonne; i++){
		D.coef[i] = coef[i] - A.coef[i];
	}
	return D;
}
	
Matrice Matrice::operator-()
{
	Matrice D(nb_ligne,nb_colonne);
		
	for(int i=0; i<nb_ligne*nb_colonne; i++){
		D.coef[i] = - coef[i];
	}
		
	return D;
}
	
double* Matrice::operator[](int i)
{
	if(i < nb_ligne){
		return coef+(i*nb_colonne);
	}
	ErreurDepassement ed;
	throw ed;	
}
	
Matrice Matrice::transposer()
{
	Matrice T(nb_colonne, nb_ligne);
	
	for(int i=0; i<nb_colonne; i++){
		for(int j=0; j<nb_ligne; j++){
			T[i][j] = (*this)[j][i];
		}
	}
	return T;	
}

ostream& operator<<(ostream &out, Matrice &m)
{	
	for(int i=0; i<m.nb_ligne; i++){
			
		for(int j=0; j<m.nb_colonne; j++){
		
			out << m.coef[j + i*m.nb_colonne] << "\t" ;
		}
			
		out << endl;
	}
	return out;
}
	
istream& operator>>(istream &in, Matrice &m)
{
	cout << "Entrez les coefficients de votre matrice :" << endl; 
	for(int i=0; i<m.nb_ligne*m.nb_colonne; i++){
		in >> m.coef[i];
	}
		
	return in;
}
	
Matrice Matrice::sous_matrice(int i, int j)
{
	Matrice sm (nb_ligne-1, nb_colonne-1);
		
	for(int k=0; k<i; k++){
		for(int l=0; l<j; l++){
			sm[k][l] = (*this)[k][l];
		}
	}
		
	for(int k=i+1 ; k<nb_ligne; k++){
		for(int l=0; l<j; l++){
			sm[k-1][l] = (*this)[k][l];
		}
	}
		
	for(int k=0 ; k<i; k++){
		for(int l=j+1; l<nb_colonne; l++){
			sm[k][l-1] = (*this)[k][l];
		}
	}
		
	for(int k=i+1 ; k<nb_ligne; k++){
		for(int l=j+1; l<nb_colonne; l++){
			sm[k-1][l-1] = (*this)[k][l];
		}
	}
				
	return sm;
}	
	
double Matrice::determinant()
{
	if(nb_ligne != nb_colonne){
		ErreurMatriceCarre emc; 
		throw emc;
	}
		
	double s=0.0;
		
	if(nb_ligne == 1 && nb_colonne == 1){
		s = (*this)[0][0];
	}
		
	for(int i=0; i<nb_ligne; i++){
		s += pow(-1,i)*((*this)[0][i])*(sous_matrice(0,i).determinant());
	}
		
	return s;
}
	
double Matrice::cofacteur(int i, int j)
{
	return pow(-1, i+j)*sous_matrice(i,j).determinant();
}
		
Matrice Matrice::comatrice(){
	if(nb_ligne != nb_colonne){
		ErreurMatriceCarre emc;
		throw emc;
	}
		
	Matrice co(nb_ligne, nb_colonne);
		
	for(int i=0; i<nb_ligne; i++){
		for(int j=0; j<nb_colonne; j++){
			co[i][j] = cofacteur(i,j);
		}
	}
		
	return co;
}
	
Matrice Matrice::operator*(double x)
{
	Matrice p(nb_ligne, nb_colonne);
	
	for(int i=0; i<nb_ligne*nb_colonne; i++){
		p.coef[i] = coef[i] * x;
	}
		
	return p;
}
	
Matrice Matrice::inverse()
{
	if(nb_ligne != nb_colonne){
		ErreurMatriceCarre emc;
		throw emc;
	}
		
	if(determinant() == 0){
		ErreurDeterminant ed;
		throw ed;
	} 
	
	return (comatrice().transposer())*(1/determinant());
		

}
	
double Matrice::get_nb_ligne() const
{
	return nb_ligne;
}
	
double Matrice::get_nb_colonne() const
{
	return nb_colonne;
}
	
double Matrice::get_coef(int i) const 
{
	return coef[i];
}
/*
void Matrice::set_coef()
{
	cout << "Entrez les coefficients de votre matrice : \n" << endl; 
		
	for(int i=0; i<nb_colonne*nb_ligne; i++)
		cin >> coef[i];
}
	
void Matrice::afficher_matrice()
{
	for(int i=0; i<nb_ligne * nb_colonne; i++)
		cout << coef[i] << "\t";
	cout << " " << endl;
}
*/

/*void Matrice::rand(int value)
{

   for(int i=0; i<nb_ligne; i++){
      
      for(int j=0; j<nb_colonne; j++){
		  
		(*this)[i][j]=rand()%value;
		
		}
	}

} 
*/

int Matrice::get_compteur()
{
   return compteur;
}

void Matrice::reset_compteur()
{
   compteur = 0;
}
