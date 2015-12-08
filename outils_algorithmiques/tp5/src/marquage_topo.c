#include <stdlib.h>
#include <stdio.h>
#include <ll_adj.h>

int main(int argc, char* argv[])
{
    cell_som* graphe = charge_graphe(argv[1]);

    if(marquage_topologique(graphe, argv[2]))
    {
        printf("Le graphe a ete correctement marqué topologiquement dans le fichier.\n");
    } else
    {
        printf("Le graphe ne peut etre topologiquement marquable.\n");
    }

    return 0;

}
