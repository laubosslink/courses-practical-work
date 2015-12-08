/******************************************************************************/
/* C. PORQUET                    LL_ADJ.c                           Mars 2004 */
/* Stratégie : les sommets sont empilés dans la liste des sommets,            */
/*             les arcs sont empilés dans leur liste de successeurs           */
/* On accède au graphe par un pointeur sur la liste des sommets               */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <lifo.h>
#include <ll_adj.h>

struct Cell_som {
	int sommet;
	int nb_pred;
    struct Cell_arc *psucc;
    struct Cell_som *suivant;
};

struct Cell_arc {
	cell_som *pextrem;
    struct Cell_arc *suivant;
};

/*----------------------------------------------------------------------------*/
cell_som *creer_sommet(int som, cell_som *suiv)
{
	cell_som *p;

	p = (cell_som *) malloc(sizeof(cell_som));

	if (p == NULL)
		exit(-1);

	p->sommet = som;
	p->psucc = NULL;
	p->suivant = suiv;

	return p;
}
/*----------------------------------------------------------------------------*/
cell_arc *creer_arc(cell_arc *suiv, cell_som *pext)
{
	cell_arc *p;

	p = (cell_arc *) malloc(sizeof(cell_arc));

	if (p == NULL)
		exit(-1);

	p->pextrem = pext;
	p->suivant = suiv;

	return p;
}
/*----------------------------------------------------------------------------*/
void affiche_successeurs(cell_arc *psuc)
{
	cell_arc *p = psuc;

	while (p) {
		printf("<%d>\t",p->pextrem->sommet);
        p = p->suivant;
	}

	printf("\n");
}
/*----------------------------------------------------------------------------*/
void affiche_graphe(cell_som *graphe)
{
	cell_som *p = graphe;

	while (p){
		printf("Successeurs de %d : ",p->sommet);
        affiche_successeurs(p->psucc);
		p = p->suivant;
	}

	printf("\n");
}
/*----------------------------------------------------------------------------*/
/* recherche d'un sommet dans la liste des sommets */
cell_som *cherche(int som, cell_som *graphe)
{
	cell_som *p = graphe;

	while(p){
		if(p->sommet == som)
			return p;

		p = p->suivant;
    }

	return NULL;
}
/*----------------------------------------------------------------------------*/
cell_som* charge_graphe(char *nom_fichier)
{
	cell_som *graphe, *pori, *pext;
	cell_arc *parc;

	int nsom, narc;

	FILE *fp;

	int i, ori, ext;

	fp = fopen(nom_fichier,"rt");

	if (fp == NULL)
		exit(-1);

	fscanf(fp,"%d %d",&nsom,&narc);

	graphe = NULL;

	for (i=0;i<narc;i++)
    {
		fscanf(fp,"%d %d",&ori,&ext);
		pori = cherche(ori,graphe);

		if (!pori)
		{
			pori = creer_sommet(ori,graphe);
            pori->nb_pred = 0;
			graphe = pori;
		} /* on empile */

		pext = cherche(ext,graphe);

		if (!pext){
			pext = creer_sommet(ext,graphe);
			pext->nb_pred = 0;
			graphe = pext;
		} /* on empile */

		pext->nb_pred++;

		parc = creer_arc(pori->psucc, pext);
		pori->psucc = parc; /* on empile */
    }

	fclose(fp);
	return graphe;
}
/******************************************************************************/
int marquage_topologique_envisageable(cell_som* graphe)
{
    cell_som* psom = graphe;

    while(psom != NULL)
    {
        if(psom->nb_pred == 0)
            return 1;

        psom = psom->suivant;
    }

    return 0;
}
/******************************************************************************/
void ecrire_marquage(char* file, Lifo lifo_no_pred)
{
    int i, length;

    length = lifo_length(lifo_no_pred);

    FILE* f = fopen(file, "w");

    if(f == NULL){
        fprintf(stderr, "Impossible d'ouvrir le fichier '%s'", file);
    }

    cell_som* psom;

    /* écriture du nombre de sommet dans le fichié */
    fprintf(f, "%d\n", length);

    /* on dépile chaque élément */
    for(i=1; i<=length; i++)
    {
        psom = (cell_som*) lifo_pop_elmt(lifo_no_pred);
        /* écriture du numéro du marquage topologique, et l'index du sommet associé */
        fprintf(f, "%d %d\n", i, psom->sommet);
    }

    fclose(f);
}
/******************************************************************************/
void retirer_virtuellement_sommet(cell_som* psom, Lifo lifo_no_pred)
{
    cell_arc* parc;
    cell_som* pext;

    /* .. on l'ajoute dans la pile */
    lifo_add_elmt(lifo_no_pred, psom);

    /* .. on le retire virtuellement en déclarant que son nb_pred = -1 */
    psom->nb_pred = -1;

    /* .. on parcours ces arcs (successeurs) pour décrémenter le nombre de prédcesseurs */
    parc = psom->psucc;

    while(parc != NULL)
    {
        pext = parc->pextrem;

        if(pext->nb_pred > 0)
            pext->nb_pred--;

        parc = parc->suivant;
    }
}
/******************************************************************************/
int marquage_topologique(cell_som* graphe, char* file)
{
    /* si ce graphe ne contient aucun nbpred == 0, alors le marquage n'est pas possible */
    if(!marquage_topologique_envisageable(graphe))
    {
        return 0;
    }

    int marquage_topo_realise = 1;

    Lifo lifo_no_pred = lifo_init();

    cell_som* psom;

    /* Tant qu'il y a des sommets sans prédecesseurs */
    do
    {
        psom = graphe;

        /* on parcours les sommets pour trouver ceux sans prédecesseurs */
        while(psom != NULL)
        {

            /* si un sommet est sans prédecesseur...*/
            if(psom->nb_pred == 0)
            {
                retirer_virtuellement_sommet(psom, lifo_no_pred);
            }

            psom = psom->suivant;
        }
    } while(marquage_topologique_envisageable(graphe));

    /**
     * on vérifie que l'ensemble des sommets à un nb_pred == -1, sinon le marquage n'est pas complet
     * ce qui implique qu'il n'est pas possible, car des éléments n'ont pas étés empilés
     */
    psom = graphe;

    while(psom != NULL)
    {
        if(psom->nb_pred != -1)
            marquage_topo_realise = 0;

        psom = psom->suivant;
    }

    /* Si il y a un fichier spécifié, et que le marquage topo est fait, on l'enregistre */
    if(marquage_topo_realise == 1)
    {
        /* on met l'ordre topo de la pile dans le bon ordre (numéro 1 topo en premier, etc..) */
        lifo_no_pred = lifo_reverse(lifo_no_pred);

        if(file != NULL)
        {
            ecrire_marquage(file, lifo_no_pred);
        }
    }

    return marquage_topo_realise;
}

/******************************************************************************/
void affiche_marquage_topo(char* file)
{
	int nb_som, i;
	int index_sommet, index_topo;

    FILE* f = fopen(file, "r");

    if(f == NULL){
        fprintf(stderr, "Impossible d'ouvrir le fichier '%s'", file);
    }

	fscanf(f, "%d", &nb_som);

	for(i=0; i<nb_som; i++){
		fscanf(f, "%d %d", &index_topo, &index_sommet);
		printf("Le sommet %d est attribue au numero %d d'apres l'attribution topologique\n", index_sommet, index_topo);
	}

    fclose(f);
}
/******************************************************************************/
int nb_pred(int sommet, cell_som *graphe)
{
    int n=0;

    cell_som* c = cherche(sommet, graphe);

    if(c != NULL){
        n = c->nb_pred;
    }

    return n;
}
