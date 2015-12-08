#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int main(int argc, char* argv[]){
	int number;
	
	printf("Quel exercice executer ?\n");
	printf("1: exercice1_a\n");
	printf("2: exercice1_b\n");
	printf("3: exercice2_a\n");
	printf("4: exercice2_c\n");
	printf("5: exercice2_d\n");
	printf("6: exercice3\n");
	
	if(argc < 2)
		scanf("%d", &number);
	else
		number = atoi(argv[1]);
	
	switch(number){
		case 1:
			return exercice1_a();
		case 2:
			return exercice1_b();
		case 3:
			return exercice2_a();
		case 4:
			return exercice2_c();
		case 5:
			return exercice2_d();
		case 6:
			return exercice3();
		default:
			fprintf(stderr, "exercice %d innexistant\n", number);
	}
	
	return EXIT_SUCCESS;
}
