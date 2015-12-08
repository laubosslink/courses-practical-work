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
 * @file exception.cpp
 * Implementation des méthodes exceptions.
 */


#include <exception.h>
using namespace std; 


Erreur::Erreur(const char* message): exception(),message(message) {}
	
const char* Erreur::what() const throw() {
    return message;
}

ErreurTaille::ErreurTaille() : Erreur("Taille incompatible") {}

ErreurDepassement::ErreurDepassement() : Erreur("Depassement de ligne") {}

ErreurMatriceCarre::ErreurMatriceCarre() : Erreur("Matrice non carrée") {}

ErreurDeterminant::ErreurDeterminant() : Erreur("Determinant nul") {}
