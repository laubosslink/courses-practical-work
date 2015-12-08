#include <stdio.h>
#include <stdlib.h>

int main()
{
	float nombre;
	float total;
	int n=0;

	do {
		printf("Veuillez entrer une note compris entre 0 et 20: ");
		scanf("%f", &nombre);

		if(nombre < 0 || nombre > 20)
		{
			if(nombre != 99)
				printf("Mauvais nombre\n");

			continue;
		}

		total += nombre;
		n++;

	} while(nombre != 99);

	printf("Moyenne : %f", total/n);

	return EXIT_SUCCESS;
}

