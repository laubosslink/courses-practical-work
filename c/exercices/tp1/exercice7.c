#include <stdio.h>
#include <stdlib.h>

int main(){

	/* -- Toute cette partie contient l'initialisation de variable de type size_t -- */

	/* La variable ici se nomme sz_char et va contenir comme valeur la taille que représente le type char 
	 * normalement la sz_char = 1; mais cela dépend de l'architecture ! c'est pourquoi on fait appel à la fonction sizeof(..) */
	size_t sz_char = sizeof(char);

	/* Equivalente à la ligne d'au dessus */
	size_t sz_uchar = sizeof(unsigned char);

	/* La taille du type short*/
	size_t sz_short = sizeof(short);

	/* Equivalente a la ligne d'haut dessus */
	size_t sz_ushort = sizeof(unsigned short);

	/* Va contenir ce qu'occupe la taille du type entier */
	size_t sz_int = sizeof(int);

	/* du type long */
	size_t sz_long = sizeof(long);

	/* du type long long */
	size_t sz_llong = sizeof(long long);

	/* Equivalent a sizeof(int); */
	size_t sz_uint = sizeof(unsigned int);

	/* Equivalente a sizeof(long int)*/
	size_t sz_ulong = sizeof(unsigned long int);

	/* Equivalente a sizeof(long long) */
	size_t sz_ullong = sizeof(unsigned long long);

	/* -- fin de l'initiallisation de variable de type size_t -- */

	/* %u permet d'afficher un entier naturel autrement dit : un unsigned int 
	 * L'ensemble des printf affichent les valeurs des variables ci-dessus */
	printf("%u %u %u %u\n", sz_char, sz_uchar, sz_short, sz_ushort);
	printf("%u %u %u \n", sz_int, sz_long, sz_llong);
	printf("%u %u %u \n\n", sz_uint, sz_ulong, sz_ullong);

	/* contiendra aucun caractère de la table ascii */
	/* il y aura exactement la valeur suivante en binaire : 11111011 soit 0xfb ou 0373 en octal*/
	char c1 = -100;

	/* va contenir 20 soit en ASCII DC4(device control 4) */
	unsigned char uc1 = 200;

	/* -10*-10 = 100 on aura exactement en binaire : 01100100 */
	short s1=c1*c1;

	/* -10*20 = -200 ca rentre dans un type short qui a 2 octet allant de -32768 a 32767 */
	short us2= c1*uc1;

	/* -100*100 = -10000 ok */
	long i1= -s1*s1;

	/* -200*-200=40000 range ok */
	int i2= us2*us2;

	/* 20*20=400 */
	unsigned int ui1 = uc1*uc1;

	/* -10000*40000=-400000000 soit -4*10^8 bien loin de la limite a ~10^18*/
	long long ll1 = i1*i2;

	/* 10000*400 = 4000000 range ok */
	long ui2 = -i1*ui1;

	/* -10000*-10000=100000000 soit 1*10^8 */
	unsigned long long ull1 = i1*i1;

	/* affiche s1=100 (%d pour décimal)*/
	printf("s1=%d\n", s1);

	printf("us2=%d\n", us2);

	printf("i1=%d\n", i1);

	printf("i2=%d\n", i2);

	/* %u pour %d avec unsigned, soit un entier naturel
	 * ca va donc afficher : ui1=400 */
	printf("ui1=%u\n", ui1);

	/* %I64d permet d'afficher un entier avec indentation de 64 espaces */
	printf("ll1=%I64d\n", ll1);

	printf("ui2=%u\n", ui2);

	printf("ull1=%I64u\n", ull1);

	/* c) Pour obtenir le même résultat que le TP il suffit d'enlever le I64 aux deux instructions ci dessus pour n'avoir que %d */

	/* d)
	 * i1 devient long (pour résoudre le cas de ll1 on aurait aussi pu caster en (long) i1 lors de la multiplication, ce qui évite de changer le type de la variable)
	 * ui2 devient long
	 * pour les affichages utilisations de %ld ou %lld en fonction du type
	 * */
	printf("\nreponse à d)\n");
	printf("ll1=%lld\n", ll1);
	printf("ui2=%ld\n", ui2);
	printf("ull1=%lld\n", ull1);

	return EXIT_SUCCESS;
}
