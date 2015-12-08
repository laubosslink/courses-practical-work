#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 80

/**
 * Permet de savoir si le charactère entré est un séparateur
 * @param char c le charactère à tester
 * @return 1 si c'est le cas, 0 sinon
 */
int is_separator(char c){
	return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
//	return (c == ' ' || c == '\'' || c == '\0' || c == ',' || c == '!' || c == '.');
}

/**
 * Permet de savoir combien de charactères il faut lire avant de tomber sur le prochain séparateur
 * @param char *str la chaine de caractère à tester
 * @return un entier si on trouve un prochain séparateur, -1 sinon
 */
int size_to_read(char *str){
	int i;
	
	for(i=0; i<strlen(str); i++)
	{
		if(is_separator(*(str+i)))
			return i;
	}
	
	return -1;
}

int size_to_read2(char *str, int size){
	int i;
	
	for(i=0; i<size; i++)
	{
		if(is_separator(*(str+i)))
			return i;
	}
	
	return -1;
}

/**
 * Permet de savoir le nombre d'éléments qu'il y aura dans le tableau
 * @param char *str la chaine de caractère à tester
 * @return le nombre d'élements
 */
int array_size(char *str){
	int i, n=0;
	
	//if(!is_separator(str[0])) n++;
	
	for(i=0; i<strlen(str); i++){
		if(is_separator(*(str+i)))
			n++;
	}
	
	return n;
}


int array_size_2(char *str, int size){
	int i, n=0;

	if(!is_separator(str[0])) n++;
	
	for(i=1; i<size-1; i++){
		if(is_separator(*(str+i)) && !is_separator(*(str+i+1)))
			n++;
	}
	
	return n;
}

/**
 * Permet d'entrer une chaine de caractere dans l'entree stdin et d'en sortir un tableau de caractere
 * @return tableau de caractere
 */
char* input_str(){
	int i=0;
	char c;
	char *str;
	
	str = malloc(sizeof(char) * LIMIT);
	
	/* resolve issue from main use */
	if((c=getchar()) == '\n')
		c=' ';
	
	while((c = getchar()) != '\n'){
		if(strlen(str) > LIMIT)
			break;
		str[i++] = c;
	}
	
	str = realloc(str, sizeof(char) * i);
	
	return str;
}

/**
 * Permet d'inverser les caracteres d'une chaine de caractere, et de retourner un tableau representatif
 * @param str la chaine de caractere d'entree
 * @return la chaine de caractere inverse
 */
char* reverse_str(char *str){
	int i;
	
	char *inverse;
	
	inverse = malloc(sizeof(char) * (strlen(str)+1));
	
	/* A partir de la chaine, nouvelle chaine avec longueur minimale, et caractères inversés */
	for(i=0; i<strlen(str); i++){
		inverse[i] = str[strlen(str)-i-1];
	}
	
	/* Ajout d'un caractère espace de simulation a la fin (ne pas mettre \0 car il n'est pas compter dans strlen) */
	inverse[strlen(str)] = ' ';
	
	return inverse;
}

void parse_punc_str(char *str){
	int i, j, k;
	char **str_parse;
	
	str_parse = (char**) malloc(sizeof(char*) * array_size(str));
	
	/* Pour chaque élements */
	for(k=0, i=0; i<=strlen(str) && size_to_read(str+i) != -1; i+=size_to_read(str+i)+1, k++)
	{
		/* Si on se trouve sur un séparateur, on passe à l'itération suivante */
		if(is_separator(str[i]))
			continue;
			
		/* On alloue le nombre de caractère pour la chaine courrante */
		str_parse[k] = (char*) malloc(sizeof(char) * size_to_read(str+i));
		
		/* Pour chaque caractère, on l'ajoute dans notre tableau de chaine de caractère */
		for(j=0; j<size_to_read(str+i); j++){
			str_parse[k][j] = str[j+i];
		}
		
		/* On affiche la chaine de caractère courrante */
		printf("%s\n", str_parse[k]);
		
		free(str_parse[k]);
	}
	
	free(str_parse);
	
	//return str_parse;
}

void parse_punc_str_opt(char *str){
	int i, j, size, k, str_length;
	char **r;
	
	char *istr = str;
	
	r = (char **) malloc(sizeof(char *) * array_size(str));
	
	str_length = strlen(str);
	size = array_size_2(str, str_length);

	for(i=0; i<size; i++){
		r[i] = str;
		str[size_to_read2(str, str_length)] = '\0';

		k=1;
		while(is_separator(str[size_to_read2(str, str_length)+k])) k++;

		str += size_to_read2(str, str_length)+k;
	}
	
	for(i=0; i<size; i++){
			printf("%s\n", r[i]);
	}
}

int exercice2_c(){
	char *in, *inverse;
	char **str;
	
	printf("Veuillez entrer une chaine: ");
	in = input_str();
	inverse = reverse_str(in);
	
	printf("%s\n", inverse);
	parse_punc_str(inverse);
	
	parse_punc_str_opt(inverse);

	//free(inverse);
	//free(in);
	
	return EXIT_SUCCESS;
}
