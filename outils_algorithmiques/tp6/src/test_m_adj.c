#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <lifo.h>
#include <m_adj.h>

#define EXEMPLE_GRAPHE_FILE "extra/test_exemple1.txt"
#define EXEMPLE_GRAPHE_TOPO_FILE "extra/test_exemple1_topo.txt"

int main()
{
    int tests = 0;

    m_adj m = m_adj_load_file(EXEMPLE_GRAPHE_FILE);

/* @todo tester la fonction m_adj_get_duration_from_to(..) */

/* test des fonctions qui permettent de récupérer une durée d'un sommet */

    tests = m_adj_get_duration(m, 1) == 6;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 1 : %d == 6\n", m_adj_get_duration(m, 1));
#endif

    tests = m_adj_get_duration(m, 2) == 3;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 2 : %d == 3\n", m_adj_get_duration(m, 2));
#endif

    tests = m_adj_get_duration(m, 3) == 6;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 3 : %d == 6\n", m_adj_get_duration(m, 3));
#endif

    tests = m_adj_get_duration(m, 4) == 2;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 4 : %d == 2\n", m_adj_get_duration(m, 4));
#endif

    tests = m_adj_get_duration(m, 5) == 4;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 5 : %d == 4\n", m_adj_get_duration(m, 5));
#endif

    tests = m_adj_get_duration(m, 6) == 3;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 6 : %d == 3\n", m_adj_get_duration(m, 6));
#endif

    tests = m_adj_get_duration(m, 0) == 0;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 0 : %d == 0\n", m_adj_get_duration(m, 0));
#endif

    tests = m_adj_get_duration(m, 7) == 1 && tests;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 7 : %d == 1\n", m_adj_get_duration(m, 7));
#endif

    tests = m_adj_get_duration(m, 8) == 0 && tests;

#if DEBUG_AFFICHE == 1
    printf("duree sommet 8 : %d == 0\n", m_adj_get_duration(m, 8));
    printf("\n");
#endif

/* test de la fonction qui permet de récupérer les sommet prédécesseur d'un sommet */

    Lifo l = m_adj_pred(m, 6);
    int *elmt;

#if DEBUG_AFFICHE == 1
    printf("predecesseur de 6 : {");
#endif

    if(lifo_is_empty(l))
        tests = 0;

    while(!lifo_is_empty(l))
    {
        elmt = (int *) lifo_pop_elmt(l);

#if DEBUG_AFFICHE == 1
    printf("%d, ", *elmt);
#endif

        /* si on ne trouve pas le sommet 1 ou 4 */
        if(*elmt != 1 && *elmt != 4)
        {
            tests = 0;
        }
    }

#if DEBUG_AFFICHE == 1
    printf("} <=> {1, 4}\n");
#endif

    l = m_adj_pred(m, 1);

#if DEBUG_AFFICHE == 1
    printf("predecesseur de 1 : {");
#endif

    if(lifo_is_empty(l))
        tests = 0;

    while(!lifo_is_empty(l))
    {
        elmt = (int *) lifo_pop_elmt(l);

#if DEBUG_AFFICHE == 1
    printf("%d, ", *elmt);
#endif

        /* si on ne trouve pas le sommet 0*/
        if(*elmt != 0)
        {
            tests = 0;
        }
    }

#if DEBUG_AFFICHE == 1
    printf("} <=> {0}\n");
    printf("\n");
#endif

/* test que les noms de tache renvoye correspondent à celle du sommet */
    tests = strcmp(m_adj_get_tache(EXEMPLE_GRAPHE_FILE, 1), "A") == 0 && tests;

#if DEBUG_AFFICHE == 1
    printf("tache du sommet 1 : %s == A\n", m_adj_get_tache(EXEMPLE_GRAPHE_FILE, 1));
#endif

    tests = strcmp(m_adj_get_tache(EXEMPLE_GRAPHE_FILE, 4), "D") == 0 && tests;

#if DEBUG_AFFICHE == 1
    printf("tache du sommet 4 : %s == D\n", m_adj_get_tache(EXEMPLE_GRAPHE_FILE, 4));
#endif

    tests = strcmp(m_adj_get_tache(EXEMPLE_GRAPHE_FILE, 8), "Omega") == 0 && tests;

#if DEBUG_AFFICHE == 1
    printf("tache du sommet 8 : %s == Omega\n", m_adj_get_tache(EXEMPLE_GRAPHE_FILE, 8));
#endif
    tests = strcmp(m_adj_get_tache(EXEMPLE_GRAPHE_FILE, 6), "F") == 0 && tests;

#if DEBUG_AFFICHE == 1
    printf("tache du sommet 6 : %s == F\n", m_adj_get_tache(EXEMPLE_GRAPHE_FILE, 6));
    printf("\n");
#endif

/* test de la fonction m_adj_get_sommet */

    tests = m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "A") == 1 && tests;

#if DEBUG_AFFICHE == 1
    printf("numero du sommet A : %d == 1\n", m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "A"));
#endif

    tests = m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "D") == 4 && tests;


#if DEBUG_AFFICHE == 1
    printf("numero du sommet D : %d == 4\n", m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "D"));
#endif

    tests = m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "Omega") == 8 && tests;


#if DEBUG_AFFICHE == 1
    printf("numero du sommet Omega : %d == 8\n", m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "Omega"));
#endif

    tests = m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "F") == 6 && tests;

#if DEBUG_AFFICHE == 1
    printf("numero du sommet F : %d == 6\n", m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "F"));
    printf("\n");
#endif

/* test de la fonction m_adj_dtot */

    tests = m_adj_dtot(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "G")) == 9 && tests;

    tests = m_adj_dtot(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "F")) == 6 && tests;

    tests = m_adj_dtot(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "D")) == 3 && tests;

    tests = m_adj_dtot(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "E")) == 3 && tests;

#if DEBUG_AFFICHE == 1
    /* @todo les tests de dtot */
#endif

#if DEBUG_AFFICHE == 1
    m_adj_date_plus_tot(EXEMPLE_GRAPHE_FILE, EXEMPLE_GRAPHE_TOPO_FILE, m);
    printf("\n");
#endif

/* tests de m_adj_dtard*/

    tests = m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "Omega")) == 10 && tests;

#if DEBUG_AFFICHE == 1
    printf("date plus tard Omega : %d == 10\n", m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "Omega")));
#endif

    tests = m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "G")) == 9 && tests;

#if DEBUG_AFFICHE == 1
    printf("date plus tard G : %d == 9\n", m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "G")));
#endif

    tests = m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "F")) == 6 && tests;

#if DEBUG_AFFICHE == 1
    printf("date plus tard F : %d == 6\n", m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "F")));
#endif

    tests = m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "D")) == 4 && tests;

#if DEBUG_AFFICHE == 1
    printf("date plus tard D : %d == 4\n", m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "D")));
#endif

    tests = m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "E")) == 5 && tests;

#if DEBUG_AFFICHE == 1
    printf("date plus tard E : %d == 5\n", m_adj_dtard(m, m_adj_get_sommet(EXEMPLE_GRAPHE_FILE, "E")));
    printf("\n");
#endif

#if DEBUG_AFFICHE == 1
    m_adj_date_plus_tard(EXEMPLE_GRAPHE_FILE, EXEMPLE_GRAPHE_TOPO_FILE, m);
    printf("\n");
#endif

	if(tests == 1)
		printf("m_adj: \033[32mOK\033[0m\n");
	else
		printf("m_adj: \033[31mproblemes durant les tests\033[0m\n");

	return 0;
}
