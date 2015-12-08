#include <stdlib.h>
#include <stdio.h>
#include <ll_adj.h>

int main()
{
    int tests = 0;
	cell_som *graphe;

    graphe = charge_graphe("extra/test_graphe_non_marquable_boucle.txt");

    tests = marquage_topologique(graphe, NULL) == 0;

    graphe = charge_graphe("extra/test_graphe_non_marquable_boucle.txt");

#if DEBUG_AFFICHE == 1
    printf("graphe non marquable : %d == 1\n", marquage_topologique(graphe, NULL) == 0);
#endif

/**
 * test du nombre de predecesseurs (implémenté dans la fonction charge_graphe),
 * sur chaque sommet du graphe marquable
 */
    graphe = charge_graphe("extra/test_graphe_marquable.txt");

    tests = nb_pred(0, graphe) == 0 && tests;

#if DEBUG_AFFICHE == 1
    printf("nb_pred sommet 0 : %d == 0\n", nb_pred(0, graphe));
#endif

    tests = nb_pred(1, graphe) == 1 && tests;

#if DEBUG_AFFICHE == 1
    printf("nb_pred sommet 1 : %d == 1\n", nb_pred(1, graphe));
#endif

    tests = nb_pred(2, graphe) == 1 && tests;

#if DEBUG_AFFICHE == 1
    printf("nb_pred sommet 2 : %d == 1\n", nb_pred(2, graphe));
#endif

    tests = nb_pred(3, graphe) == 1 && tests;

#if DEBUG_AFFICHE == 1
    printf("nb_pred sommet 3: %d == 1\n", nb_pred(3, graphe));
#endif

    tests = nb_pred(4, graphe) == 1 && tests;

#if DEBUG_AFFICHE == 1
    printf("nb_pred sommet 4 : %d == 1\n", nb_pred(4, graphe));
#endif

    tests = nb_pred(5, graphe) == 2 && tests;

#if DEBUG_AFFICHE == 1
    printf("nb_pred sommet 5 : %d == 2\n", nb_pred(5, graphe));
#endif

    tests = nb_pred(6, graphe) == 1 && tests;

#if DEBUG_AFFICHE == 1
    printf("nb_pred sommet 6 : %d == 1\n", nb_pred(6, graphe));
#endif

    graphe = charge_graphe("extra/test_graphe_marquable.txt");

    tests = marquage_topologique(graphe, "extra/test_marquage_topologique_graphe_marquable.txt") && tests;

    graphe = charge_graphe("extra/test_graphe_marquable.txt");

#if DEBUG_AFFICHE == 1
    printf("graphe marquable : %d == 1\n", marquage_topologique(graphe, NULL) == 1);
#endif

/**
 * On vérifie que le marquage est réalisé dans un bon ordre
 */

    FILE *f = fopen("extra/test_marquage_topologique_graphe_marquable.txt", "r");

    int sommet;

    fseek(f, 4, SEEK_CUR);
    fscanf(f, "%d", &sommet);

    tests = sommet == 0 && tests;

#if DEBUG_AFFICHE == 1
    printf("Ordre topo n°1 se trouve le sommet : %d == 0\n", sommet);
#endif

    fseek(f, 3, SEEK_CUR);
    fscanf(f, "%d", &sommet);

    tests = sommet == 4 && tests;

#if DEBUG_AFFICHE == 1
    printf("Ordre topo n°2  se trouve le sommet : %d == 4\n", sommet);
#endif

    fseek(f, 3, SEEK_CUR);
    fscanf(f, "%d", &sommet);

    tests = sommet == 1 && tests;

#if DEBUG_AFFICHE == 1
    printf("Ordre topo n°3 se trouve le sommet : %d == 1\n", sommet);
#endif

    /* on passe 3 lignes * 4 (nombre d'octet : '%d %d\n') pour regarder la dernière (correspond au dernier sommet marqué) */
    fseek(f, 4 * 3, SEEK_CUR);

    /* on passe le numéro d'ordre du dernier sommet pour juste récupérer le numéro de sommet */
    fseek(f, 2, SEEK_CUR);
    fscanf(f, "%d", &sommet);

    tests = sommet == 5 && tests;

#if DEBUG_AFFICHE == 1
    printf("Ordre topo n°7 se trouve le sommet : %d == 5\n", sommet);
#endif

#if DEBUG_AFFICHE == 1
	affiche_marquage_topo("extra/test_marquage_topologique_graphe_marquable.txt");
#endif

	if(tests == 1)
		printf("ll_adj: \033[32mOK\033[0m\n");
	else
		printf("ll_adj: \033[31mproblemes durant les tests\033[0m\n");

	return 0;
}
