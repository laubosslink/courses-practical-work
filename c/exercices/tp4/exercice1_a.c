#include <stdio.h>
#include <stdlib.h>

void saisir(int *a, int *b)
{
	printf("a:");
	scanf("%d", a);
	
	printf("b:");
	scanf("%d", b);
}

int exercice1_a(void) {
	int a, b;
	saisir(&a,&b);
	printf("a=%d b=%d\n", a, b); 
	return EXIT_SUCCESS;
}
