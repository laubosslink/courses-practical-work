#include <stdio.h>
#include <stdlib.h>

int main(){
	int entier;

	/* Le do while permet de demander une premeire fois */
	do {
		printf("Veuillez entrer un entier entre 0 et 9:");
		scanf("%d", &entier);
	} while(entier < 0 || entier > 9); /* Tant que le nombre <0 ou >9 on le redemande à l'utilisateur */

	switch(entier)
	{
		case 0:
			printf("zero");
			break;
		case 1:
			printf("un");
			break;
		case 2:
			printf("deux");
			break;
		case 3:
			printf("trois");
			break;
		case 4:
			printf("quatre");
			break;
		case 5:
			printf("cinq");
			break;
		case 6:
			printf("six");
			break;
		case 7:
			printf("sept");
			break;
		case 8:
			printf("huit");
			break;
		case 9:
			printf("neuf");
			break;
		default:
			printf("loop problem");
	}

	printf("\n");

	return EXIT_SUCCESS;
}
