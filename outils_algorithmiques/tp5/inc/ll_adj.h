#ifndef INCLUDED_H_LL_ADJ
#define INCLUDED_H_LL_ADJ

#include <lifo.h>

typedef struct Cell_arc cell_arc;

typedef struct Cell_som cell_som;

cell_som *creer_sommet(int som, cell_som *suiv);

cell_arc *creer_arc(cell_arc *suiv, cell_som *pext);

void affiche_successeurs(cell_arc *psuc);

void affiche_graphe(cell_som *graphe);

cell_som *cherche(int som, cell_som *graphe);

cell_som* charge_graphe(char *nom_fichier);

/**
 * Permet de connaitre le nombre de prédecesseur d'un sommet
 * @param sommet le sommet
 * @param le graphe dans lequel on cherche
 * @return un entier représentant le nombre de prédecesseur
 */
int nb_pred(int sommet, cell_som *graphe);

/**
 * Permet de savoir si on peut entreprendre un marquage topologique
 * c-a-d si il y a au moins un sommet qui n'a aucun predecesseur
 * dans le graphe donné.
 * @param graphe le graphe dans lequel chercher
 * @return 1 si on peut entreprendre, 0 sinon
 */
int marquage_topologique_envisageable(cell_som* graphe);

/**
 * Permet de réaliser un marquage topologique, et de l'enregistrer dans le fichier
 * @param graphe sur lequel on réalise le marquage
 * @param file fichier dans lequel on enregistre le marquage topologique
 * @return 1 si le marquage topologique a été possible sur le graphe, 0 sinon
 */
int marquage_topologique(cell_som* graphe, char* file);

/**
 * Permet d'afficher un marquage topologique, a partir d'un
 * fichier contenant le marquage topologique
 * @see marquage_topologique
 * @param file le fichier contenant le marquage
 */
void affiche_marquage_topo(char* file);

#endif
