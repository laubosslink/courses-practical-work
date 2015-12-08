/**
 * Permet d'afficher le prompt
 */
void affiche_prompt();

/**
 * Permet d'executer une/des lignes de commandes
 * @see ligne_commande <ligne_commande.h>
 */
void execute_ligne_commande();

/**
 * Permet une commande com avec le tableau d'arguments argv.
 */
int lance_commande(int in, int out, char *com, char **argv);
