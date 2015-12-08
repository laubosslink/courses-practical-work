#include <iostream>
#include <math.h>

#include <Lanceur.h>
#include <Clou.h>
#include <Planche.h>

// pour la destruction, c particulier => lequel d'un pere va detruire un même successeur ? idee simple, boolean pour dire si oprphelin

// relier avec ceux d'en dessous

Planche::Planche(int nbr_compteurs)
{
	nb_compteurs = nbr_compteurs;

	compteur_final = new Compteur();

	compteurs = (Compteur**) new Compteur[nbr_compteurs];

	// creation des compteurs
	for(int i=0; i<nbr_compteurs; i++)
	{
		compteurs[i] = new Compteur(compteur_final);
	}

	// affectation des compteurs a la construction
	construction = (Obstacle**) new Obstacle[nbr_compteurs];

	for(int i=0; i<nbr_compteurs; i++)
	{
		construction[i] = compteurs[i];
	}

	Clou* clou_courrant;

	// Creation des clous
	for(int i=nbr_compteurs-1; i>=0; i--)
	{
		for(int j=0; j<i; j++)
		{
			clou_courrant = new Clou(construction[j], construction[j+1]);

			if(construction[j]->orphelin())
			{
				construction[j]->set_orphelin(false);
				clou_courrant->set_gere_des_gauche(true);
			}

			if(construction[j+1]->orphelin())
			{
				construction[j+1]->set_orphelin(false);
				clou_courrant->set_gere_des_droit(true);
			}

			// creation du fils, et sauvegarde dans le tableau tmp
			construction[j] = clou_courrant;
		}
	}

	// rq: construction[0] <=> clou racine
	lanceur = new Lanceur(construction[0]);
}

void Planche::simulation(int nbr)
{
	for(int i=0; i<nbr; i++)
	{
		lanceur->lancer();
	}

	for(int i=0; i<nb_compteurs; i++)
	{
		std::cout << "Compteur(" << i << ") : " << round(((float)(compteurs[i])->getCompteur()/compteur_final->getCompteur()) * 100.0) << "%" << std::endl;
	}
}

void Planche::affiche_compteurs()
{
	for(int i=0; i<nb_compteurs; i++)
	{
		std::cout << "Compteur(" << i << ") : " << (compteurs[i])->getCompteur() << std::endl;
	}

	std::cout << "Compteur final : " << compteur_final->getCompteur() << std::endl;
}

Planche::~Planche()
{
	lanceur->~Lanceur();

	for(int i=0; i<nb_compteurs; i++)
	{
		compteurs[i] = nullptr;
		construction[i] = nullptr;
	}

	compteur_final = nullptr;


}
