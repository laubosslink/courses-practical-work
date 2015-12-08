#ifndef INC_H_L_ADJ
#define INC_H_L_ADJ

typedef struct t_cellule T_CELLULE;
typedef struct t_ladj T_LADJ;

typedef enum eCouleur{
    BLANC=1,
    NOIR=2,
    GRIS=3
} COULEUR;

T_CELLULE *creer_cellule(int extr, float val, T_CELLULE *suiv);

void affiche_liste(T_CELLULE *p);

T_LADJ init_ladj(int nsom, int nar);

void affiche_graphe(T_LADJ g);

T_LADJ charge_graphe(char *nom_fichier);

T_LADJ inverse(T_LADJ g);

int parcour_profondeur_prefixe(T_LADJ l);

void visite_profondeur_prefixe(T_CELLULE** tab, int sommet, int *temps, int *pred, COULEUR *couleur, int *debut, int *fin, int* nb_noeud);

int parcour_profondeur_suffixe(T_LADJ l);

void visite_profondeur_suffixe(T_CELLULE** tab, int sommet, int *temps, int *pred, COULEUR *couleur, int *debut, int *fin, int* nb_noeud);

int parcour_largeur(T_LADJ l);

void visite_largeur(T_CELLULE** tab, COULEUR* couleur, int* d, int* pred, int sommet, int* nb_noeud);

#endif
