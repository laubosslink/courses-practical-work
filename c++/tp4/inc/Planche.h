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
#ifndef INC_PLANCHE_H
#define INC_PLANCHE_H

#include <Compteur.h>
#include <Obstacle.h>
#include <Lanceur.h>

/**
 * Classe qui représente une planche
 */
class Planche
{
private:
	Lanceur* lanceur;

	int nb_compteurs;
	Compteur** compteurs;
	Compteur* compteur_final;

	Obstacle** construction;
public:
	/**
	 * Constructeur de la plance
	 * @param nbr_compteurs permet de spécifier le nombre de compteurs
	 */
	Planche(int nbr_compteurs);

	/**
	 * Destructeur d'une planche
	 */
	~Planche();

  /**
	 * Permet de réaliser une simulation
	 * @param nbr le nombre de simulations
	 */
	void simulation(int nbr);

  /**
	 * Permet d'afficher les compteurs
	 */
	void affiche_compteurs();
};

#endif
