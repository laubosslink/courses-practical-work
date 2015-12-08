/**
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 * 
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written premission of the authors
 */
 
/**
 * @author PARMENTIER Laurent <parmentier@ecole.ensicaen.fr, laubosslink@society-lbl.com>
 * @author ELHIMDI Yasmine
 * @version 1.0
 * @date 09-10-2014
 */
 
/** 
 * @file hamming.c
 */

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int bit(int x, int i, int n)
{
	return (x>>(n-i)) & 1;
}

int flip(int x, int i, int n)
{
	return x^(1<<(n-i));
}

/* codage_7_4 hamming 7,4 */
int codage_7_4(int m)
{
	int x = 0;

	/* x3 = m1 */
	x = bit(m, 1, 4)<<4; // 4 = 7 - 3

	/* x5 = m2 */
	x ^= bit(m, 2, 4)<<2; // 2 = 7 - 5

	/* x6 = m3  */
	x ^= bit(m, 3, 4)<<1;

	/* x7 = m4 */
	x ^= bit(m, 4, 4);

	/* calculs des sommes de controles*/

	/* x1 = (x3 + x5 + x7)%2 <=> (m1 + m2 + m4)%2*/
	x ^= ((bit(m, 1, 4) + bit(m, 2, 4) + bit(m, 4, 4)) % 2)<<6;

	/* x2 = (x3 + x6 + x7)%2 <=> (m1 + m3 + m4)%2 */
	x ^= ((bit(m, 1, 4) + bit(m, 3, 4) + bit(m, 4, 4)) % 2)<<5;

	/* x4 = (x5 + x6 + x7)%2 <=> (m2 + m3 + m4)%2*/
	x ^= ((bit(m, 2, 4) + bit(m, 3, 4) + bit(m, 4, 4)) % 2)<<3;

	return x;
}

int canal_sym(int x, int n, int p)
{
	int i, p_c;

	/* controle l'entree utilisateur */
	if(p > 100 || p < 0)
		p = 50;

	/* adaptation a rand() % 100 qui retourne un nombre [0-99] */
	p -= 1;


	for(i=1; i<=n; i++)
	{
		p_c = rand() % 100;
		if(p_c < p)
			x = flip(x, i, n);
	}

	return x;
}

int syndrome_7_4(int y, int n)
{
	int s = 0;

	/* calcul de s0 = (y1 + y3 + y5 + y7 [2])*/
	s = (bit(y, 1, 7) + bit(y, 3, 7) + bit(y, 5, 7) + bit(y, 7, 7)) % 2;

	/* calcul de s1 */
	s ^= ((bit(y, 2, 7) + bit(y, 3, 7) + bit(y, 6, 7) + bit(y, 7, 7)) %2) << 1;

	s ^= ((bit(y, 4, 7) + bit(y, 5, 7) + bit(y, 6, 7) + bit(y, 7, 7)) %2) << 2;

	return s;
}

int correction_syndrome_7_4(int y, int s)
{
	return y = y^(1<<(7-s));
}

int *code_hamming_7_4()
{
	int* code_hamming = (int *) malloc(sizeof(int) * 16);

	int i;

	for(i=0; i<16; i++)
		code_hamming[i] = codage_7_4(i);

	return code_hamming;
}

int distance_hamming(int n, int x, int y)
{
	int i, delta=0;

	for(i=1; i<=n; i++){
		if(bit(x,i,n) != bit(y,i,n))
			delta++;
	}

	return delta;
}

int distance_min_code(int n, int K, int* code)
{
	int d = distance_hamming(n,code[0],code[1]);

	int i,j;

	for(i=0; i<K; i++){
		for(j=i+1; j<K;j++){
			if(distance_hamming(n,code[i],code[j])<d)
				d = distance_hamming(n,code[i],code[j]);
		}
	}

	return d;
}

int factoriel(int n)
{
	if(n == 0)
		return 1;

	return factoriel(n-1) * n;
}

float coef_binomial(int n, int k)
{
	return factoriel(n)/(factoriel(k) * factoriel(n - k));
}

int capacite_correction(int d)
{
	return floor((d-1)/2);
}

float code_correct(int n, float p, int e)
{
	int i;

	float proba = 0;

	for(i=0; i<=e; i++)
	{
		proba += coef_binomial(n, i) * powf(p, (float)i) * powf((float)1-p, (float)n-i);
	}

	return proba;
}

int main()
{
	srand(time(NULL));

	int m = 8;
	int c = codage_7_4(m);
	int c_b;

	int* c_h;

	printf("codage_7_4 (m=%d): %d\n", m, c);

	c_b = canal_sym(c, 7, 10);

	/* remarque : on ne peut corriger qu'une seule erreur */
	if(syndrome_7_4(c_b, 7) != 0)
	{
		printf("syndrome_7_4: %d\n", syndrome_7_4(c_b, 7));
		printf("codage_7_4 corrige: %d\n", correction_syndrome_7_4(c_b, syndrome_7_4(c_b, 7)));
	}

	printf("\n");

	c_h = code_hamming_7_4();

	printf("codage_7_4 de hamming (7,4) : \n");

	for(int i=0; i<16; i++)
		printf("Code (i=%d) : %d\n", i, c_h[i]);

	printf("\nDistance minimale du code de Hamming(7,4) : %d \n\n", distance_min_code(7,16,c_h)); 

	printf("Probabilite qu'il y ait au plus une  erreur : %f\n", code_correct(7, 0.25, 1));
	//printf("Probabilite qu'il y ait au plus deux erreur : %f\n", code_correct(7, 0.25, 2));

	int tmp_n, tmp_c, nb_juste=0, tmp_cs, tmp_corrige;

	for(int t=0; t<1000; t++)
	{
		tmp_n = rand()%16;
		tmp_c = codage_7_4(tmp_n);
		tmp_cs = canal_sym(tmp_c, 7, 25);

		if(syndrome_7_4(tmp_cs, 7) == 0)
		{
			nb_juste++;
		} else {
			tmp_corrige = correction_syndrome_7_4(tmp_cs, syndrome_7_4(tmp_cs, 7));

			if(tmp_n == tmp_corrige)
			{
				printf("YES\n");
				nb_juste++;
			}
		}
	}

	// retourne ~0.22 soit 22%, malgres de multiples recherche nous ne trouvons pas le problème..
	printf("Probabilite que le decodage hamming soit correct : %f\n", nb_juste/1000.0);

	printf("\n");

	return 0;
}
