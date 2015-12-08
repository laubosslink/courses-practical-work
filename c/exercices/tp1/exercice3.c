#include <stdio.h>
#include <stdlib.h>

int main(){
	int note1, note2, note3;

	printf("Affichage de la moyenne\n:");

	printf("Premiere note: ");
	scanf("%d", &note1);
	printf("\n");
	printf("Deuxieme note: ");
	scanf("%d", &note2);
	printf("\n");
	printf("Troisieme note: ");
	scanf("%d", &note3);
	printf("\n");

	printf("Moyenne : %d", (note1+note2+note3)/3);

	return EXIT_SUCCESS;
}
