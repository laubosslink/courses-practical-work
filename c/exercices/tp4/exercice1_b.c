#include <stdio.h>
#include <stdlib.h>
#include "swap.h"

void saisir3(int *a, int *b, int *c)
{
	printf("a:");
	scanf("%d", a);
	
	printf("b:");
	scanf("%d", b);
	
	printf("c:");
	scanf("%d", c);
}

void trier3(int *a, int *b, int *c)
{	
	if(*a > *b)
		swap(a, b);
	
	if(*b > *c)
		swap(b, c);
	
	if(*a > *b)
		swap(a, b);	
}

int exercice1_b(void) {
	int a, b, c;
	saisir3(&a,&b,&c);
	trier3(&a,&b,&c);
	printf("Voici vos trois nombres rangés dans l'ordre croissant : %d %d %d\n", a, b, c);
	return 0;
}

