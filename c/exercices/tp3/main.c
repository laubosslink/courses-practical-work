#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int main(){
	int number;
	
	printf("Quel exercice executer ?\n");
	printf("1: exercice1\n");
	printf("2: exercice2\n");
	printf("3: exercice3\n");
	printf("4: exercice4\n");
	printf("5: exercice5\n");
	printf("6: exercice6\n");
	scanf("%d", &number);
	
	switch(number){
		case 1:
			exercice1();
			break;
		case 2:
			exercice2();
			break;
		case 3:
			exercice3();
			break;
		case 4:
			exercice4();
			break;
		case 5:
			exercice5();
			break;
		case 6:
			exercice6();
			break;
	}
	
	return EXIT_SUCCESS;
}
