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
#ifndef INC_OBSTACLE_H
#define INC_OBSTACLE_H

/**
 * Class permettant de représenter un obstacle
 */
class Obstacle
{
private:
	bool palet_present;
	bool est_orphelin;


public:
	/**
	 * Constructeur d'un obstacle
	 * @param orphelin (optional) par défaut à true, il permet de gérer la desallocation
	 */
	Obstacle(bool orphelin=true) : palet_present(false), est_orphelin(orphelin){}

	/**
	 * Destructeur virtuel, permet l'appel du destructeur fils
	 */
	virtual ~Obstacle();

	/**
	 * Méthode recoitPalet virtuelle
	 */
	virtual void recoitPalet();

  /**
	 * Methode qui permet de mettre palet_present a false
   */
	void perdPalet();

	/**
	 * Permet de vérifier la présent d'un palet sur l'obstacle
	 */
	bool paletPresent();

  /**
	 * Methode liée a la désallocation.
	 * Permet de dire q'un obstacle est orphelin ou non
	 * @param orphelin true ou false
	 */
	void set_orphelin(bool orphelin);

	/**
	 * Permet de vérifier si l'obstacle est orphelin ou non
	 * @return true si il l'est, false sinon
	 */
	bool orphelin();
};

#endif
