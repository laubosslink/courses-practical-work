#include <stdio.h>
#include <stdlib.h>

int main(){
	char c;
	int hexa;

	printf("Char -> ASCII(hex), ASCII(hex) -> Char\n");

	printf("Char: ");

	scanf("%c", &c);
	printf("ASCII: %x", c);

	printf("\nHexa: ");

	scanf("%x", &hexa);
	printf("Lettre: %c", hexa);

	return EXIT_SUCCESS;
}
