#include <stdio.h>
#include <stdlib.h>

int main(){
	int decimal;

	do{
		printf("Veuillez entrer une valeur:");
		scanf("%d", &decimal);
		/* Si le nombre est négatif, on quitte la boucle */
		if(decimal < 0) break;

		printf("valeur en octal %o\n", decimal);
		printf("valeur en hexa %x\n", decimal);
		printf("valeur en HEXA %X\n", decimal);
	} while(decimal >= 0);

	printf(">fin<");

	return EXIT_SUCCESS;
}
