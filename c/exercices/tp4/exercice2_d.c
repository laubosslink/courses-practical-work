#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialise(void *art, char c, int num, int prix){
	int i;
	
	int * ptr_int=(int*)((char*)art +1);
	
	*((char *)art) = c;
	*ptr_int=num;
	*(ptr_int+1)=prix;

}

void afficheInfo(void *art){
	
	int *ptr_art = (int *)(((char *)art)+1);
	
	switch(*((char *)art))
	{
		case 'L':
			printf("Livre ");
			break;
		case 'C':
			printf("CD/DVD ");
			break;
		case 'M':
			printf("Matériel audio ");
			break;
		default:
			printf("Unknown");
			break;
	}
	
	printf("n°%d,", *ptr_art);
	
	printf(" de prix %.2f euros\n", (float)(*(ptr_art+1))/100);
}

int exercice2_d()
{
	char article[9];
	initialise(article, 'L', 3456, 4370);
	afficheInfo(article);
	return EXIT_SUCCESS;
}
