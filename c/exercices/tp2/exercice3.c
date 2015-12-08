#include <stdio.h>
#include <stdlib.h>

int main()
{
	int number, i, longueur_binaire, tmp;
	
	printf("Entrer un nombre:");
	scanf("%d", &number);

	tmp=number;
	while(tmp>0)
	{
		printf("%d", tmp%2);
		tmp /= 2;
	}

	printf("\n");

	// determine la longueur binaire
	for(i=0, longueur_binaire=1; (number/longueur_binaire)>1; i++, longueur_binaire*=2);

	// sens inverse de lecture de la numérotation binaire base 2 
	for(; i>=0; i--)
	{
		if(number/longueur_binaire == 1)
			printf("1");
		else
			printf("0");

		number %= longueur_binaire;
		longueur_binaire /= 2;
	}
	
	
	printf("\n");
	
	return EXIT_SUCCESS;
}
