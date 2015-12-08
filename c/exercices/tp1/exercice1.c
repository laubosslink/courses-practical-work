#include <stdio.h>
#include <stdlib.h>

/* fonction main() qui est appelé par défaut lors de l'execution du programme */
int main()
{
	/* déclaration de deux variables de type entier */
	int x=12, y=25;

	/* Affichage de la : somme, difference, quotient, reste */
	printf("somme : %d\n", x + y);
	printf("difference : %d\n", x - y);
	printf("quotient : %d\n", x / y);
	printf("reste division : %d\n", x % y);

	/* aucune gestion sur les codes d'erreur par défaut on retourne 0 soit le EXIT_SUCCESS de stdlib.h, il n'y a aucun probleme */
	return EXIT_SUCCESS;
}
