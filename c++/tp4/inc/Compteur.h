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
* @date 13-11-2014
*/
#ifndef INC_COMPTEUR_H
#define INC_COMPTEUR_H

#include <Obstacle.h>

/**
 * La classe du compteur
 */
class Compteur  : public Obstacle
{
private:
	int compteur;
	Obstacle* suivant;
public:
	/**
	 * Constructeur d'un compteur sans fils
	 */
	Compteur() : compteur(0), suivant(nullptr) {}

  /**
	 * Constructeur d'un compteur avec un fils
	 */
	Compteur(Obstacle* suivant) : compteur(0), suivant(suivant) {}

  /**
	 * Destructeur d'un compteur
	 */
	~Compteur();

  /**
	 * Permet de recevoir un palet, et d'incrémenter le compteur
	 */
	void recoitPalet();

  /**
	 * Permet de récupérer le compteur
	 * @return le nombre de passage du palet
	 */
	int getCompteur();
};

#endif
