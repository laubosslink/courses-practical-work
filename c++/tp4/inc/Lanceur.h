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
#ifndef INC_LANCEUR_H
#define INC_LANCEUR_H

#include <Obstacle.h>

/**
 * Class qui représente un lanceur
 */
class Lanceur
{
private:
	Obstacle* obstacle_depart;
public:
	/**
	 * Constructeur d'un lanceur sans obstacle de départ
	 */
	Lanceur(): obstacle_depart(nullptr) {}

	/**
	 * Constructeur d'un lanceur avec un obstacle de départ
	 */
	Lanceur(Obstacle* obstacle) : obstacle_depart(obstacle) {}

	/**
	 * Destructeur du lanceur
	 */
	~Lanceur();

	/**
	 * Permet de lancer l'obstacle de départ
	 * => l'appel de obstacle_depart->recoitPalet()
	 */
	void lancer();
};

#endif
