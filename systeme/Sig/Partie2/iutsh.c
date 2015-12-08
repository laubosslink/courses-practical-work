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


int lance_commande(int in, int out, char *com, char **argv)
{
	int err;
	pid_t child;

	child = fork();

	if(child == -1)
		return -1;

	if(child == 0)
	{
		if(in != 0)
		{
			close(0);
			dup(in);
			close(in);
		}

		if(out != 1)
		{
			close(1);
			dup(out);
			close(out);
		} 

		err = execvp(com, argv);
		
		fprintf(stdout, "TEST");

		/* La suite n'est pas execute*/
		/*
		if(err == -1)
		{
			fprintf(stderr, "Problème avec la commande '%s'\n", com);
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
		*/
	} else
	{
		if(in != 0)
			close(in);
		if(in != 1)
			close(out);
	} 

	return child;
}

void execute_ligne_commande()
{
	/* Initialisation des variables */
	int *flag, *nb;
	char ***cmd;
	int err=0;
	int nCurrentCmd = 0;
	int pipefd[2];
	pid_t child;

	flag = (int *)malloc(sizeof(int));
	nb = (int *)malloc(sizeof(int));

	/* Attente qu'une commande soit entrée */
	cmd = ligne_commande(flag, nb);

	if(cmd == NULL)
		return;

	/* TODO le flag pour arrière plan du travail suivant : */

	/* On parcour chaque commande */
	for(; nCurrentCmd<*nb; nCurrentCmd++)
	{

		if(pipe(pipefd) != 0)
			fprintf(stderr, "Problème avec le pipe.\n");	

		/* Première ou dernier commande */
		if(nCurrentCmd == 0 || nCurrentCmd == *nb-1)
		{
			if(nCurrentCmd == 0 && *nb != 1)
			{
				printf("first cmd\n");
				fflush(stdout);
				child = lance_commande(0, pipefd[1], cmd[nCurrentCmd][0], cmd[nCurrentCmd]);
			} else if(*nb == 1)
			{ 
				printf("1 cmd\n");
				fflush(stdout);
				child = lance_commande(0, 1, cmd[nCurrentCmd][0], cmd[nCurrentCmd]);
			} else	
			{
				printf("last cmd\n");
				fflush(stdout);
				child = lance_commande(pipefd[0], 1, cmd[nCurrentCmd][0], cmd[nCurrentCmd]);
			}	
		} else 
		{
			
			printf("btw cmd\n");
			fflush(stdout);
			child = lance_commande(pipefd[0], pipefd[1], cmd[nCurrentCmd][0], cmd[nCurrentCmd]);
			
		}
		
		waitpid(child, NULL, 0);

		printf("Un proc de termine %d.\n", child);
		fflush(stdout);

		if(err == EXIT_FAILURE)
			fprintf(stderr, "Problème avec la commande '%s'\n", cmd[nCurrentCmd][0]);
	}

	/* On attend que la commande se termine pour continuer */
	while(waitpid(-1, NULL, WNOHANG)>0);

	libere(cmd);

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
