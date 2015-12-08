/******************************************************************************/
/* C. PORQUET                    L_ADJ.c                            Mars 2004 */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <l_adj.h>
#include <file.h>

struct t_cellule
{
	int extremite; /* les sommets */
	float valuation;
	struct t_cellule *suivant;
};

struct t_ladj	/* listes d'adjacence */
{
	int nbsom, nbar;
	T_CELLULE **tab;  /* tableau de pointeur de cellule */
};

#define RIEN -1
#define INFINI -1

/*----------------------------------------------------------------------------*/
int parcour_largeur(T_LADJ l)
{
    int connexe=1;
    int u, v=l.nbsom;
    
    int *nb_noeud = (int *) malloc(sizeof(int));
    
    COULEUR* couleur = (COULEUR*) malloc(sizeof(COULEUR) * v);
    int* pred = (int*) malloc(sizeof(int) * v);
    int* d = (int*) malloc(sizeof(int) * v);

    for(u=0; u<v; u++){
        couleur[u]=BLANC;
        d[u]=INFINI;
        pred[u]=RIEN;
    }

    for(u=0; u<v; u++){
        if(couleur[u] == BLANC){
			*nb_noeud = 0;
			
            visite_largeur(l.tab, couleur, d, pred, u, nb_noeud);

			printf("\nIl y a %d noeuds dans la composante connexe du sommet %d\n", *nb_noeud, u);

            /* Si une couleur est blanche après la première visite,
             * alors la visite n'a pas abouti sur l'ensemble des sommet
             * ce qui implique que le graphe n'est pas connexe.
             */
            if(u > 0)
                connexe = 0;
        }
    }

    return connexe;

}
/*----------------------------------------------------------------------------*/
void visite_largeur(T_CELLULE** tab, COULEUR* couleur, int* d, int* pred, int sommet, int* nb_noeud)
{
    int u;
    
    Fifo f = makeFifo();
    T_CELLULE* c = (T_CELLULE*) malloc(sizeof(T_CELLULE));

    (*nb_noeud)++;
    couleur[sommet] = GRIS;
    d[sommet] = 0;
    pred[sommet] = RIEN;

    addFifoElmt(sommet,f);

    while(!emptyFifo(f))
    {
        u = popFifoElmt(f);
        c = tab[u];

        while(c != NULL)
        {
            if(couleur[c->extremite] == BLANC)
            {
                couleur[c->extremite] = GRIS;
                d[c->extremite] = d[u] + 1;
                pred[c->extremite] = u;
                addFifoElmt(c->extremite, f);
                (*nb_noeud)++;
            }
            c = c->suivant;
        }

        couleur[u] = NOIR;
        printf("%d ", u);
    }
}
/*----------------------------------------------------------------------------*/
int parcour_profondeur_prefixe(T_LADJ l){
    int connexe=1;
    int *debut, *fin;
    int u, v=l.nbsom, temps;

    int *nb_noeud = (int *) malloc(sizeof(int));
    
    debut = (int *) malloc(sizeof(int) * v);
    fin = (int *) malloc(sizeof(int) * v);

    COULEUR *couleur = (COULEUR *) malloc(sizeof(COULEUR) * v);
    int *pred = (int *) malloc(sizeof(int) * v);

    for(u=0; u<v; u++){
        couleur[u] = BLANC;
        pred[u] = RIEN;
    }

    temps = 0;

    for(u=0; u<v; u++){
        if(couleur[u] == BLANC){
			*nb_noeud = 0;
			
            visite_profondeur_prefixe(l.tab, u, &temps, pred, couleur, debut, fin, nb_noeud);

			printf("\nIl y a %d noeuds dans la composante connexe du sommet %d\n", *nb_noeud, u);
			
            if(u > 0)
                connexe = 0;
        }
    }

    return connexe;
}
/*----------------------------------------------------------------------------*/
void visite_profondeur_prefixe(T_CELLULE** tab, int sommet, int *temps, int *pred, COULEUR *couleur, int *debut, int *fin, int* nb_noeud){
    T_CELLULE *c;

    couleur[sommet] = GRIS;

    *temps += 1;

    debut[sommet] = *temps;

    c = tab[sommet]; /* première cellule */

    printf("%d, ", sommet);
    while(c != NULL){
        if(couleur[c->extremite] == BLANC){
            pred[c->extremite] = sommet;
            visite_profondeur_prefixe(tab, c->extremite, temps, pred, couleur, debut, fin, nb_noeud);
        }

        c = c->suivant; /* cellule suivante */
    }

	(*nb_noeud)++;
    couleur[sommet] = NOIR;

    *temps += 1;
    fin[sommet] = *temps;
}
/*----------------------------------------------------------------------------*/
int parcour_profondeur_suffixe(T_LADJ l){
    int connexe=1;
    int *debut, *fin;
    int u, v=l.nbsom, temps;

    int *nb_noeud = (int *) malloc(sizeof(int));
    
    debut = (int *) malloc(sizeof(int) * v);
    fin = (int *) malloc(sizeof(int) * v);

    COULEUR *couleur = (COULEUR *) malloc(sizeof(COULEUR) * v);
    int *pred = (int *) malloc(sizeof(int) * v);

    for(u=0; u<v; u++){
        couleur[u] = BLANC;
        pred[u] = RIEN;
    }

    temps = 0;

    for(u=0; u<v; u++){
        if(couleur[u] == BLANC){
			*nb_noeud = 0;
			
            visite_profondeur_suffixe(l.tab, u, &temps, pred, couleur, debut, fin, nb_noeud);

			printf("\nIl y a %d noeuds dans la composante connexe du sommet %d\n", *nb_noeud, u);
			
            if(u > 0)
                connexe = 0;
        }
    }

    return connexe;
}
/*----------------------------------------------------------------------------*/
void visite_profondeur_suffixe(T_CELLULE** tab, int sommet, int *temps, int *pred, COULEUR *couleur, int *debut, int *fin, int* nb_noeud){
    T_CELLULE *c;
	
    couleur[sommet] = GRIS;

    *temps += 1;

    debut[sommet] = *temps;

    c = tab[sommet]; /* première cellule */

    while(c != NULL){
        if(couleur[c->extremite] == BLANC){
            pred[c->extremite] = sommet;
            visite_profondeur_suffixe(tab, c->extremite, temps, pred, couleur, debut, fin, nb_noeud);
        }

        c = c->suivant; /* cellule suivante */
    }

	(*nb_noeud)++;
	
    couleur[sommet] = NOIR;
    printf("%d, ", sommet);

    *temps += 1;
    fin[sommet] = *temps;
}
/*----------------------------------------------------------------------------*/
T_CELLULE *creer_cellule(int extr, float val, T_CELLULE *suiv)
{
	T_CELLULE *p;

	p = (T_CELLULE *) malloc(sizeof(T_CELLULE));

	if (p == NULL)
		exit(-1);

	p->extremite = extr;
	p->valuation = val;
	p->suivant = suiv;

	return p;
 }
/*----------------------------------------------------------------------------*/
void affiche_liste(T_CELLULE *p)
{
	while (p)
    {
		printf("<%5d - %5.1f>\t",p->extremite,p->valuation);
        p = p->suivant;
    };

	printf("\n");
}
/*----------------------------------------------------------------------------*/
T_LADJ init_ladj(int nsom, int nar) /* allocation dynamique et initialisation */
{
    T_LADJ g;

    g.nbsom = nsom; g.nbar = nar;
    g.tab = (T_CELLULE **)calloc(nsom,sizeof(T_CELLULE *));
    if (g.tab == NULL)
        exit(-1);

    return g;
}
/*----------------------------------------------------------------------------*/
void affiche_graphe(T_LADJ g)
{
    int i;

    for (i=0;i<g.nbsom;i++)
    {
        if (g.tab[i]) {
            printf("Successeurs de %d : ",i);
            affiche_liste(g.tab[i]);
        }
    }

    printf("\n");
}
/*----------------------------------------------------------------------------*/
T_LADJ charge_graphe(char *nom_fichier)
{
    T_LADJ g;

    int nsom, nar;

    FILE *fp;

    int i, ori, ext;

    float val = 0;

    T_CELLULE *p;

    fp = fopen(nom_fichier,"rt");

    if (fp == NULL)
        exit(-1);

    fscanf(fp,"%d %d",&nsom,&nar);

    g = init_ladj(nsom,nar);

    for (i=0;i<nar;i++)
    {
//        fscanf(fp,"%d %d %f",&ori,&ext,&val);

        fscanf(fp,"%d %d",&ori,&ext); /* on a des fichiers sans valuation */

//        p = creer_cellule(ext,val,g.tab[ori]);

        p = creer_cellule(ext,val,g.tab[ori]);

        g.tab[ori] = p;  /* on empile */
     }

    fclose(fp);

    return g;
}
/*----------------------------------------------------------------------------*/
T_LADJ inverse(T_LADJ g)
{
    T_LADJ g_inverse;

    int i;

    T_CELLULE *p, *q;

    g_inverse = init_ladj(g.nbsom,g.nbar);

    for (i=0; i<g.nbsom; i++)
    {
        p = g.tab[i];

        while (p)
        {
            q = creer_cellule(i,p->valuation,g_inverse.tab[p->extremite]);
            g_inverse.tab[p->extremite] = q; /* on empile */
            p = p->suivant;
        }
    }

    return g_inverse;
 }
/******************************************************************************/
int main(int argc, char **argv)
{
    int connexe;

    T_LADJ  g, g_inverse;

    if (argc!=2) exit(-1);

    g = charge_graphe(argv[1]);

    g_inverse = inverse(g);

    //connexe = parcour_profondeur_prefixe(g);
    connexe = parcour_profondeur_suffixe(g);

    //connexe = parcour_largeur(g);

    if(connexe){
        printf("\nLe graphe est connexe\n");
    } else {
        printf("\nLe graphe n'est pas connexe\n");
    }

    //printf("\n1er succeseur de 0 : %d\n", g.tab[0]->extremite);
    //printf("1er succeseur de 2 : %d\n", g.tab[2]->extremite);

    return 0;
}
/*******************************************************************************
Trace d'execution sur le fichier :
6
8
0 1 3
1 1 6
1 3 2
1 4 1
3 0 2
3 4 2
4 3 7
5 2 1

Successeurs de 0 : <    1 -   3.0>
Successeurs de 1 : <    4 -   1.0>      <    3 -   2.0> <    1 -   6.0>
Successeurs de 3 : <    4 -   2.0>      <    0 -   2.0>
Successeurs de 4 : <    3 -   7.0>
Successeurs de 5 : <    2 -   1.0>

Successeurs de 0 : <    3 -   2.0>
Successeurs de 1 : <    1 -   6.0>      <    0 -   3.0>
Successeurs de 2 : <    5 -   1.0>
Successeurs de 3 : <    4 -   7.0>      <    1 -   2.0>
Successeurs de 4 : <    3 -   2.0>      <    1 -   1.0>

*******************************************************************************/
