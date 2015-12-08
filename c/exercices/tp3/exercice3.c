#include <stdlib.h>
#include <stdio.h>

/**
 * show non odd alphabet from left to right on one line
 * and odd alphabet from right to left on other
 */
void alphabetTwoWay(int x)
{
	int n;

	if(x < 0)
		n=0;
	else
		n=x*2;

	for(; n<26; n+=2)
		printf("%c ", 'a'+n);

	printf("\n");

	if(x < 0)
		n=0;
	else
		n=-(x*2);

	for(; n>-26; n-=2)
		printf("%c ", 'z'+n);

	printf("\n");
}

int getColorIndexNumber(){
	char c;

	printf("(r)ouge, (o)range, (j)aune, (v)ert, (b)leu, (i)ndigo\n");
	printf("Veuillez entrer la lettre initiale d'une des couleurs: ");

	c = getchar();
	if(c == '\n')
		c = getchar();

	switch(c){
		case 'r':
			printf("rouge\n");
			return 1;
		case 'o':
			printf("orange\n");
			return 2;
		case 'j':
			printf("jaune\n");
			return 3;
		case 'v':
			printf("vert\n");
			return 4;
		case 'b':
			printf("bleu\n");
			return 5;
		case 'i':
			printf("indigo\n");
			return 6;
		default:
			return -1;
	}
}

int getOthersColorIndexNumber(){
	char c;
	
	printf("(r)ouge, (o)range, (j)aune, (v)ert, (b)leu, (i)ndigo, (n)oir, (m)agenta, (t)urquoise\n");
	printf("Veuillez entrer la lettre initiale d'une des couleurs: ");
	
	c = getchar();
	if(c == '\n')
		c = getchar();
	
	switch(c){
		case 'r':
			printf("rouge\n");
			return 1;
		case 'o':
			printf("orange\n");
			return 2;
		case 'j':
			printf("jaune\n");
			return 3;
		case 'v':
			printf("vert\n");
			return 4;
		case 'b':
			printf("bleu\n");
			return 5;
		case 'i':
			printf("indigo\n");
			return 6;
		case 'n':
			printf("noir\n");
			return 7;
		case 'm':
			printf("magenta\n");
			return 8;
		case 't':
			printf("turquoise\n");
			return 9;
		default:
			return -1;
	}
}

void exercice3()
{
	int indexColor;
	
	/* d) appel des deux fonctions en une seule instruction */
	/*do { 
		alphabetTwoWay(indexColor = getColorIndexNumber()); 
	} while(indexColor > 0);
	*/
	
	/* e) solution qui ne nécessite pas de modifier la première fonction */
	do { 
		indexColor = getOthersColorIndexNumber();
		alphabetTwoWay(indexColor);
	} while(indexColor > 0);
}
