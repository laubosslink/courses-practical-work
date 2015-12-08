#include <stdio.h>
#include <stdlib.h>

int main(){
	int n1, n2, output, choice_in, choice_out, operateur;

	printf("--- Operation en ---\n");
	printf("1: hexadecimale\n");
	printf("2: decimale\n");
	printf("3: octale\n");

	printf("\nChoix:");
	scanf("%d", &choice_in);
	
	switch(choice_in){
		case 1:
			printf("--- Veuillez entrer deux nombres hexadecimaux: ---");
			printf("\nhex1:");
			scanf("%x", &n1);
			printf("hex2:");
			scanf("%x", &n2);
			break;
		case 2:
			printf("--- Veuillez entrer deux nombres decimaux: ---");
			printf("\nn1:");
			scanf("%d", &n1);
			printf("n2:");
			scanf("%d", &n2);
			break;
		case 3:
			printf("--- Veuillez entrer deux nombres octaux: ---");
			printf("\no1:");
			scanf("%o", &n1);
			printf("o2:");
			scanf("%o", &n2);
			break;
	}

	printf("\n--- Operateur ---\n");
	printf("1: addition\n");
	printf("2: soustraction\n");
	printf("3: multiplication\n");
	printf("\nOperateur:"); 
	scanf("%d", &operateur);
	
	switch(operateur){
		case 1:
			output = n1 + n2;
			break;
		case 2:
			output = n1 - n2;
			break;
		case 3:
			output = n1 * n2;
			break;
	}
	
	printf("\n--- Affichage en --- \n");
	printf("1: hexadecimale\n");
	printf("2: decimale\n");
	printf("3: octale\n");
	
	printf("\nChoix:");
	scanf("%d", &choice_out);

	switch(choice_out){
		case 1:
			printf("\nReponse: %x\n", output);
			break;
		case 2:
			printf("\nReponse: %d\n", output);
			break;
		case 3:
			printf("\nReponse: %o\n", output);
			break;
	}

	return EXIT_SUCCESS;
}
