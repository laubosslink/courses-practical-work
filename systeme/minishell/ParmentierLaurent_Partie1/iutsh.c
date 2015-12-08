#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "ligne_commande.h"
#include "iutsh.h"


void affiche_prompt()
{
	/* Initialisation des variables */
	struct utsname infos;
	
	/* Affectation de la structure utsname (on aurai pu utiliser gethostname), mais je voulais étudier un autre chemin */
	uname(&infos);
	
	/* Affichage */
	printf("#iutsh# %s@%s:%s$ ", getenv("USER"), infos.nodename, getcwd(NULL, 0));
	fflush(stdout);
}

void execute_ligne_commande()
{
	/* Initialisation des variables */
	int *flag, *nb;
	char ***cmd;
	int child;
	int err;
	
	/* Affectation des variables */
	flag = (int *) malloc(sizeof(int));
	nb = (int *) malloc(sizeof(int)); 
	
	/* Attente qu'une commande soit entrée */
	cmd = ligne_commande(flag, nb);
	
	child = fork();
	
	/* Un nouveau processus (fils) démarre la commande 
	* @Remarque On libère 'cmd' dans le fils, pour éviter que le père ne vide
	* prématurément la variable. 	
	*/
	if(child == 0)
	{
		err = execvp(cmd[0][0], cmd[0]);
				
		if(err == -1)
		{
			fprintf(stderr, "Execution command '%s' problem.\n", cmd[0][0]);
			libere(cmd);
			exit(EXIT_FAILURE); /* Pour comprendre le errno de execvp, il faudrait utiliser la commande : execve */
		}

		libere(cmd);
		exit(EXIT_SUCCESS);		
	}


	/* Commande en premier plan (dans ce cas, le père doit attendre le proc fils) */
	if(*flag == 0)
	{
		waitpid(child, &err, 0);	
	} else if(*flag == -1) /* Le cas où le flag ne peut être lu */
	{
		fprintf(stderr, "Problème flag\n");
	}

	/* Libération de la mémoire par le père */
	free(flag);
	free(nb);
}

int main()
{
	
	while(1)
	{
		affiche_prompt();
		execute_ligne_commande();
	}

	return EXIT_SUCCESS;
}
