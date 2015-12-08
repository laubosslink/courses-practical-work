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
 * @date 01-10-2014
 */
 
/** 
 * @file Huffman_initial.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //penser à compiler avec l'option -lm 

#define NB_max 256

typedef struct noeud{
  unsigned char symbole ;
  int nb_occurences ;
  float frequence ;
  struct noeud *f_gauche, *f_droit ;
} noeud ;

/* Retourne un nouveau noeud initialisé avec les paramètres donnés en entrée */
noeud *nouveau_noeud(unsigned char symbole, int nb_occurences, noeud *gauche, noeud *droite){
  noeud *nouveau = (noeud *) malloc(sizeof(noeud)) ;
  nouveau -> symbole = symbole ;
  nouveau -> nb_occurences = nb_occurences ;
  nouveau -> f_gauche = gauche ;
  nouveau -> f_droit = droite ;
  return nouveau;
}

/* Remplit le tableau de noeuds "table" avec les caractères du fichier "fichier", 
leur nombre d'occurence et retourne le nombre de caractères du fichier */ 
int initialiser_table(char *fichier, noeud *table[NB_max]){
  unsigned char c ;
  int n = 0 ;
  FILE *f ;

  f = fopen(fichier, "r") ;
  while (fscanf(f, "%c", &c) != EOF){
      table[c] -> nb_occurences++ ; 
      n ++ ;
    }
  fclose(f) ;
  return n ;
}

/* Insere le noeud N dans le tableau de noeuds "table" trié par ordre 
   décroissant entre les indices  0 à l - 1 en respectant l'ordre décroissant */
void inserer_noeud(noeud *table[NB_max], noeud *N, int l){
  int i = l ;

  while ((i >= 1) && (table[i - 1]->nb_occurences < N->nb_occurences)) {
      table[i] = table[i - 1] ;
      i = i - 1 ;
    }
  table[i] = N ;
}

/* Trie le tableau de noeud "table" par order décroissant en supprimant les
occurences qui sont nulles et en renvoyant le nombre d'occurences non nulles. */
int trier_table(noeud *table[NB_max]){
  int i, n = 0 ;

  for (i = 1 ; i < NB_max ; i++) 
    if (table[i]->nb_occurences > 0) {
	inserer_noeud(table, table[i], n) ;
	n++ ; 
      }
    else free(table[i]) ;
  return n ;
}

/* Complete la table avec le champs frequence de chaque noeud, correspondant au  nombre d'occurence et retourne le nombre total de symbole non nul, avec multiplicité 
(a partir d'une table de N symboles non nul) */
int remplir_frequence_table(noeud *table[NB_max], int N){
  int i, n = 0 ;
  float nb ;

  for (i = 0 ; i < N ; i++)
	n = n + (table[i]->nb_occurences) ;
  for (i = 0 ; i < N ; i++){
	nb = table[i]->nb_occurences ;
	table[i]->frequence = nb/n ;
  }
  return n ;
}

/*Affiche à l'écran le contenu de la table "table" (de n noeuds) */ 
void afficher_table(noeud *table[NB_max], int n){
int i ;
printf("\nTable :\n");
  for (i = 0 ; i < n ; i++)
	printf("car%d : %c, nb : %d et freq :%.4f\n", i, table[i]->symbole, table[i]->nb_occurences, table[i]->frequence) ;
}  


/* renvoit la hauteur d'un arbre binaire donné*/
int calcul_hauteur_arbre(noeud *arbre) {
  int abr_g, abr_d;
  if (arbre == NULL) return -1;
  abr_g = calcul_hauteur_arbre(arbre -> f_gauche);
  abr_d = calcul_hauteur_arbre(arbre -> f_droit);
  if (abr_g >= abr_d) return abr_g +1;
  	else return abr_d +1;
}


/* Remplit la table "code" avec le codage de Huffman de chaque element
definit dans l'arbre correspondant de hauteur h */
void codage(noeud *arbre, char **code, char *s, int h) {
  unsigned char symbole ;

  if (arbre -> f_gauche == NULL){
      symbole = arbre->symbole ;
      s[h] = '\0';
      code[symbole] = (char *) malloc((h+1) * sizeof(char));
      strcpy(code[symbole], s); 
    }
  else {
      s[h] = '0';
      codage(arbre->f_gauche, code, s, h+1);
      s[h] = '1';
      codage(arbre->f_droit, code, s, h+1);
    }
}

/* Affiche le contenu de la table "code" vers la sortie (fichier ou sortie standard stdout) */
void afficher_codage(FILE  *f, char **code) {
  int i ;

  for (i = 0; i < NB_max ; i++)  
    if  (code[i] != NULL) 
	fprintf(f, "%c (%d) : %s\n", i, i, code[i]);
}

/* Retourne le nombre de 0 et de 1 correspondant au codage dans le texte codé 
   des lettres contenus dans arbre de hauteur h */
int nb_bits(noeud *arbre, int h)
{
  if (arbre -> f_gauche == NULL) 
	return h * arbre->nb_occurences ;
  return nb_bits(arbre->f_gauche, h + 1) + nb_bits(arbre->f_droit, h+1) ;
}

float longueur_moyenne_code(noeud *arbre, int h)
{
  if (arbre -> f_gauche == NULL) 
	return h * arbre->frequence ;
  return longueur_moyenne_code(arbre->f_gauche, h + 1) + longueur_moyenne_code(arbre->f_droit, h+1) ;
}

float entropie(noeud *table[NB_max], int n)
{
	int i;

	float entropie = 0;

	for(i=0; i<n; i++)
		entropie += table[i]->frequence * (log(table[i]->frequence)/log(2));

	entropie *= -1;

	return entropie;
}

noeud *arbre_huffman(noeud *table[NB_max], int n)
{
	int i=1;

	noeud *arbre_huffman = NULL;

	for(i=0; i<n; i++)
	{
		arbre_huffman = nouveau_noeud('.', table[n-i-1]->nb_occurences + table[n-i]->nb_occurences, table[n-i-1], table[n-i]);
		inserer_noeud(table, arbre_huffman, n-i); // pas besoin de trie, inserer_noeud s'en occupe
	}

	return arbre_huffman;
}


/******************************************************************************/

int main(int argc, char **argv) {
  noeud *table[NB_max], *arbre ;
  char *code[NB_max], *s ;
  int i, l, n, h, nb_total, lc;
 
  for (i = 0 ; i < NB_max ; i++) table[i] = nouveau_noeud(i, 0, NULL, NULL) ;
  l = initialiser_table(argv[1], table) ;
  n = trier_table(table) ;
  nb_total = remplir_frequence_table(table, n) ;
  afficher_table(table, n) ;

// Question 1 : calcul de l'entropie binaire de table
  printf("Entropie du fichier %s : %f bits\n", argv[1], entropie(table, n));
  
  /**
   * La différence d'entropie s'explique par le fait qu'il y ait l'utilisation d'une source avec 
   * avec l'utilisation d'un plus grand nombre de symbole dans le code ASCII.
   * Ainsi plus on utilise l'ensemble des symbole (du code ascii), en se raprochant d'une équiprobabilité sur 
   * l'utilisation de chaque symbole, plus on va se raprocher d'une entropie égale à 7 (dans notre cas, car maximum de 7 bits pour coder un char ASCII).
   * Ainsi les lettres du code ASCII seront de moins en moins "deterministes".
   * En revanche, plus on a une grande fréquence d'un même symbole, plus l'entropie va se rapprocher de 0.
   */

// Question 2 : construction de l'arbre de Huffman (retourne le noeud *arbre)

// Question 3 : calcul et affichage du codage :
// le passage suivant est à décommenter après la question 2 :

  arbre = arbre_huffman(table, n);
  h = calcul_hauteur_arbre(arbre) ;
  printf("hmax = %d ",h) ;
  for (i = 0 ; i < NB_max ; i++) code[i] = NULL ;
  s = (char *) malloc((h+1) * sizeof(char)) ;
  codage(arbre, code, s, 0);
  afficher_codage(stdout, code);

/* Question 4 : calcul du taux de compression : 
le passage suivant est à décommenter après la question 3 : */

  lc = nb_bits(arbre, 0);
  printf("longueur (en bits) du texte compresse = %d\n", lc) ;
  printf("longueur (en bits) du texte non compresse : %d\n", l*8);
  printf("Taux de compression : %f\n", (float)l/(lc/8.0));

// Question 5 calculer la longueur moyenne du code obtenu :
	printf("Longueur moyenne du code : %f\n", longueur_moyenne_code(arbre, 0));
	/**
	 * L'égalite s'explique par le fait que le code est efficace.
	 * L'inégalite, s'explique par le fait qu'il y a l'inégalité i != h, car 2^(-li= != p(xi)
	 * (voir premier théorème de Shannon)
	 */

return 1 ;
}
