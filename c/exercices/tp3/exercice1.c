#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* on définit la constante PI demandé */
#define PI 3.14159265

/* fonction permettant de calculer le volume d'une sphère */
float volume_sphere(int rayon)
{
	return ((4.0/3.0) * PI * (rayon * rayon * rayon));
}

/* fonction permettant de calculer l'aire d'une sphère*/
float aire_sphere(int rayon)
{
	return 4 * PI * (rayon * rayon);
}

void exercice1(){

	float rayon;

	/* on demande le rayon à l'utilisateur */
	printf("Rayon choisi ? ");
	scanf("%f", &rayon);
	
	/* on affiche le rayon, le volume de la sphère, et son aire*/
	printf("Le volume et l'aire d'une sphère de rayon %f sont respectivement %.2ef et %.2ef.\n", rayon, volume_sphere(rayon), aire_sphere(rayon));
}
