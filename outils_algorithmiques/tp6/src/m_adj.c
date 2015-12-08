#include <stdio.h>
#include <stdlib.h>
#include <lifo.h>
#include <m_adj.h>

struct m_adj
{
    int length;
    int** matrice;
};

int m_adj_get_sommet(char* filename, char* nom_tache)
{
    FILE* file;

    char nom_tache_courrante[20];

    file = fopen(filename, "r");

    if(file == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le graphe.");
    }

    int nb_sommet, nb_arc, i;

    fscanf(file, "%d %d", &nb_sommet, &nb_arc);

    /* on passe les infos sur les arcs */
    fseek(file, nb_arc * 4, SEEK_CUR);

    int sommet_courrant;

    /* on cherche le sommet */
    for(i=0; i<nb_sommet; i++)
    {
        fscanf(file, "%d", &sommet_courrant);

        fseek(file, 3, SEEK_CUR);

        fscanf(file, "%s", nom_tache_courrante);

        if(strcmp(nom_tache, nom_tache_courrante) == 0)
            return sommet_courrant;
    }

    return -1;
}

int m_adj_get_file_duration(char* filename, int sommet)
{
    FILE* file;

    char test[20];

    file = fopen(filename, "r");

    if(file == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le graphe.");
    }

    int nb_sommet, nb_arc, i;

    fscanf(file, "%d %d", &nb_sommet, &nb_arc);

    /* on passe les infos sur les arcs */
    fseek(file, nb_arc * 4, SEEK_CUR);

    int sommet_courrant, duree;

    /* on selectionne les durees */
    for(i=0; i<nb_sommet; i++)
    {
        fscanf(file, "%d %d", &sommet_courrant, &duree);

        if(sommet_courrant == sommet)
        {
            return duree;
        }

        /* on passe le nom de la tache */
        fscanf(file, "%s", test); // @todo degueulase
        //fseek(file, 2, SEEK_CUR);
    }

    return 0;
}

Lifo m_adj_pred(m_adj m, int sommet)
{
    int j;

    int* pi;

    Lifo pred = lifo_init();

    for(j=0; j<m->length; j++)
    {
        /**
         * si la valuation != -1 dans la colonne du sommet, c'est que la ligne
         * représente le numéro de sommet prédecesseur, on l'ajoute
         */
        if(m->matrice[j][sommet] != -1)
        {
            pi = (int *) malloc(sizeof(int));
            *pi = j;
            lifo_add_elmt(pred, pi);
        }
    }

    return pred;
}

Lifo m_adj_succ(m_adj m, int sommet)
{
    int j;

    int* pi;

    Lifo succ = lifo_init();

    for(j=0; j<m->length; j++)
    {
        /**
         * si la valuation != -1 dans la ligne du sommet, c'est que la colonne
         * représente le numéro de sommet successeur, on l'ajoute
         */
        if(m->matrice[sommet][j] != -1)
        {
            pi = (int *) malloc(sizeof(int));
            *pi = j;
            lifo_add_elmt(succ, pi);
        }
    }

    return succ;
}

int m_adj_max(int n1, int n2)
{
    if(n1 > n2)
        return n1;

    return n2;
}

int m_adj_min(int n1, int n2)
{
    if(n1 < n2)
        return n1;

    return n2;
}

m_adj m_adj_init(int length)
{
    m_adj m = (m_adj) malloc(sizeof(struct m_adj));

    m->length = length;

    int i, j;

    m->matrice = (int **) malloc(sizeof(int*) * length);

    for(i=0; i<length; i++)
    {
        m->matrice[i] = (int *) malloc(sizeof(int) * length);

        for(j=0; j<length; j++)
        {
            m->matrice[i][j] = -1;
        }
    }

    return m;
}

m_adj m_adj_load_file(char* filename)
{
    FILE* file;

    file = fopen(filename, "r");

    if(file == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le graphe.");
    }

    int nb_sommet, nb_arc, i, sommet_origine, sommet_arrive;

    fscanf(file, "%d", &nb_sommet);

    m_adj m = m_adj_init(nb_sommet);

    fscanf(file, "%d", &nb_arc);

    /* pour chaque arc ... */
    for(i=0; i<nb_arc; i++)
    {
        fscanf(file, "%d %d", &sommet_origine, &sommet_arrive);

        /* on l'ajoute dans la m_adj en spécifiant la valuation */
        m->matrice[sommet_origine][sommet_arrive] = m_adj_get_file_duration(filename, sommet_origine);
    }

    return m;
}

int m_adj_get_duration(m_adj m, int sommet)
{
    if(m == NULL)
    {
        fprintf(stderr, "Please specify m_adj not NULL");
        return -1;
    }

    int j;

    for(j=0; j<m->length; j++)
    {
        if(m->matrice[sommet][j] > 0)
            return m->matrice[sommet][j];
    }

    return 0;
}

int m_adj_get_duration_from_to(m_adj m, int sommet_from, int sommet_to)
{
    if(m == NULL)
    {
        fprintf(stderr, "Please specify m_adj not NULL");
        return -1;
    }

    return m->matrice[sommet_from][sommet_to];
}

int m_adj_dtot_with_current_duration(m_adj m, int sommet)
{
    // On ajoute la duree du sommet courrant
    return m_adj_dtot(m, sommet) + m_adj_get_duration(m, sommet);
}

/* dtot_k = Max(dtot_i + v_ik) ou i est une tâche qui précède k */
int m_adj_dtot(m_adj m, int sommet)
{
    Lifo preds = m_adj_pred(m, sommet);

    /* si le sommet n'a aucun prédecesseur, c'est qu'il a une duree nulle */
    if(lifo_is_empty(preds))
        return 0;

    /* dans le cas contraire on cherche le max de ces predecesseurs */

    /* on récupère le premier prédecesseur */
    int* predecesseur_courrant = lifo_pop_elmt(preds);

    int sum = m_adj_dtot_with_current_duration(m, *predecesseur_courrant);

    /* on parcours chaque prédecesseur pour comparer chaque duree et prendre la plus grande*/
    while(!lifo_is_empty(preds))
    {
        predecesseur_courrant = lifo_pop_elmt(preds);
        sum = m_adj_max(sum, m_adj_dtot_with_current_duration(m, *predecesseur_courrant));
    }

    return sum;
}

/* dtard_k = Min(dtard_i- v_ki) ou i est une tâche qui suit k */
int m_adj_dtard(m_adj m, int sommet)
{
    Lifo succs = m_adj_succ(m, sommet);

    if(lifo_is_empty(succs))
        return m_adj_dtot(m, sommet);

    int* successeur_courrant = lifo_pop_elmt(succs);

    int sum = m_adj_dtard(m, *successeur_courrant);

    while(!lifo_is_empty(succs))
    {
        successeur_courrant = lifo_pop_elmt(succs);
        sum = m_adj_min(sum, m_adj_dtard(m, *successeur_courrant));
    }

    return sum - m_adj_get_duration(m, sommet);
}

char* m_adj_get_tache(char* filename, int sommet)
{
    FILE* file;

    char* str = (char*) malloc(sizeof(char) * 20);

    file = fopen(filename, "r");

    if(file == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le graphe.");
    }

    int nb_sommet, nb_arc, i;

    fscanf(file, "%d %d", &nb_sommet, &nb_arc);

    /* on passe les infos sur les arcs */
    fseek(file, nb_arc * 4, SEEK_CUR);

    int sommet_courrant, duree;

    /* on selectionne les durees */
    for(i=0; i<nb_sommet; i++)
    {
        fscanf(file, "%d", &sommet_courrant);

        /* on passe les informations de duree*/
        fseek(file, 2, SEEK_CUR);

        /* on passe le nom de la tache */
        fscanf(file, "%s", str); // @todo degeu

        if(sommet == sommet_courrant)
        {
            return str;
        }
    }

    return str;
}

void m_adj_date_plus_tard(char* filename, char *filename_topo, m_adj m)
{
    /* on charge le fichier topo */
    FILE* f;

    f = fopen(filename_topo, "r");

    if(f == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }

    int i, nb_sommet, sommet_courrant;

    char *tache_courrante_nom;

    int tache_courrante_dtard;

    fscanf(f, "%d", &nb_sommet);

    /* on prend chaque sommet dans ordre inverse topo */
    for(i=nb_sommet; i>0; i--)
    {
        /* on passe les infos nb_arcs */
        fseek(f, 3, SEEK_CUR);

        fscanf(f, "%d", &sommet_courrant);

        tache_courrante_nom = m_adj_get_tache(filename, sommet_courrant);
        tache_courrante_dtard = m_adj_dtard(m, sommet_courrant);

       printf("La tâche %s doit commencer au plus tard la semaine %d.\n", tache_courrante_nom, tache_courrante_dtard);
    }

    return;
}

void m_adj_date_plus_tot(char* filename, char *filename_topo, m_adj m)
{
    /* on charge le fichier topo */
    FILE* f;

    f = fopen(filename_topo, "r");

    if(f == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }

    int i, nb_sommet, sommet_courrant;

    char *tache_courrante_nom;

    int tache_courrante_dtot, tache_courrante_dfin;

    fscanf(f, "%d", &nb_sommet);

    /* on prend chaque sommet dans ordre topo */
    for(i=0; i<nb_sommet; i++)
    {
        /* on passe les infos nb_arcs */
        fseek(f, 3, SEEK_CUR);

        fscanf(f, "%d", &sommet_courrant);

        tache_courrante_nom = m_adj_get_tache(filename, sommet_courrant);
        tache_courrante_dtot = m_adj_dtot(m, sommet_courrant);
        tache_courrante_dfin = tache_courrante_dtot + m_adj_get_duration(m, sommet_courrant);

        printf("La tâche %s commence au plus tot la semaine %d et sera donc finit au bout de %d semaines.\n", tache_courrante_nom, tache_courrante_dtot, tache_courrante_dfin);
    }

    return;
}
