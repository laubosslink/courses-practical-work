#include <stdio.h>
#include <stdlib.h>

int main(){
	int somme;

	printf("Veuillez entrer un montant: ");

	scanf("%d", &somme);

	printf("Montant minimum : \n");

	printf("%d billet de 10\n", somme/10);

	somme %= 10;

	printf("%d billet de 5\n", somme/5);

	somme %= 5;

	printf("%d piece de 2\n", somme/2);

	somme %= 2;

	printf("%d piece de 1\n", somme);

	return EXIT_SUCCESS;
}
