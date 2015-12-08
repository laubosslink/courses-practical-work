#include <stdio.h>
#include <stdlib.h>

int main(){
	/* Déclaration des variables, une pour l'entrée de l'utilisateur, et l'autre pour le traitement */
	double in;
	int total;

	printf("Veuillez entrer un montant: ");

	scanf("%lf", &in);

	/* pour traiter on aura besoin du modulo donc total doit representer un entier */
	total = in * 100;

	printf("Montant minimum pour %lf euros: \n", in);

	// On prend la partie entière de la division par 1000 (10.00 * 10) pour connaitre le nombre de billet de 10 euros
	printf("%d billet de 10euros\n", total/1000); // On prend la partie entière de la division par 1000 (10.00 * 10) pour connaitre le nombre de billet de 10 euros

	// Puis le reste de cette division par 1000
	total %= 1000;

	printf("%d billet de 5euros\n", total/500);

	total %= 500;

	printf("%d piece de 2euros\n", total/200);

	total %= 200;
	
	printf("%d piece de 1euro\n", total/100);
	
	total %= 100;
	
	printf("%d * 50 centimes d'euros\n", total/50);
	
	total %= 50;
	
	printf("%d * 20 centimes d'euros\n", total/20);
	
	total %= 20;
	
	printf("%d * 10 centimes d'euros\n", total/10);
	
	total %= 10;
	
	printf("%d * 5 centimes d'euros\n", total/5);

	total %= 5;
	
	printf("%d * 2 centimes d'euros\n", total/2);
	
	total %= 2;
	
	printf("%d * 1 centimes d'euros\n", total);
	
	return EXIT_SUCCESS;
}
