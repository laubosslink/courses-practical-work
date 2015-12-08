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

#ifndef INC_CLOU_H
#define INC_CLOU_H

#include <cstdlib>
#include <ctime>

#include <Obstacle.h>

/**
 * Classe qui permet de représenter un clou
 */
class Clou : public Obstacle
{
private:
	Obstacle* gauche;
	Obstacle* droite;

	// gestion désalocation
	bool gere_des_droit, gere_des_gauche;
public:
	/**
	 * Constructeur de clou
	 * @param gauche pointeur d'un obstacle gauche
	 * @param droite pointeur d'un obstacle droite
	 */
	Clou(Obstacle* gauche, Obstacle* droite) : gauche(gauche), droite(droite), gere_des_droit(false), gere_des_gauche(false) {}

	/**
	 * Destructeur d'un clou
	 * attention le destructeur détruit ces fils (droite, gauche)
	 */
	~Clou();

	/**
	 * Permet de recevoir un palet (mettre palet_present à vrai)
	 * Cette appel provoque automatiquement l'appel de:
	 * - transmetPalet()
	 * - Obstacle::perdPalet()
	 */
	void recoitPalet();

	/**
	 * Permet de transmettre le palet à un fils
	 * Utilisation des nombres aléatoires, autoprobabilité de l'avoir à gauche ou à droite
	 * Implique l'appel de recoitPalet() sur le fils selectionné par l'autoprobabilité.
	 */
	void transmetPalet();

	void set_gere_des_droit(bool val);

	void set_gere_des_gauche(bool val);
};
#endif
