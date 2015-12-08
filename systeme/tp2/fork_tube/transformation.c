/** 
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin 
 * F-14050 Caen Cedex 
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */ 

/**
 * @author El Himdi Yasmine <yasmine.elhimdi@ecole.ensicaen.fr> 
 * @author Parmentier Laurent <laurent.parmentier@ecole.ensicaen.fr> 
 */

#include <stdio.h> /* printf() */
#include <unistd.h> /* fork(), perror() */
#include <stdlib.h> /* exit() */

#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define INIT_BUFFER 64

/** REMARQUE 1)
 * important de refaire un nouveau malloc a chaque recu et ne pas garder l'alloc initial
 * suivit de ses realloc. Un utilisateur peut tres bien entrer une ligne avec 2000 caractes puis 10 000 lignes
 * avec 2 caracteres, on aurait donc un malloc important pour peu de donnees entrees
 * Apres on peut debattre sur la qte d'alloc qui sont fait, mais c'est pas l'objectif du TP !
 */

// fonction lire_clavier avec optimisation memoire (doublage realloc si on atteint la limite)
char* lire_clavier(int *i)
{
        int limit = INIT_BUFFER;
        char c;

        char* buff = (char *) malloc(sizeof(char) * limit);

        while((c = fgetc(stdin)) != '\n')
        {
                if(*i >= limit-1)
                {
                        limit *= 2;
                        buff = (char *) realloc(buff, sizeof(char) * limit);
                }

                buff[(*i)++] = c;
        }

        buff[*i] = '\0';

        return buff;
}

int eof_present(char *s, int c)
{
	int i=0;

	for(; i<c; i++)
		if(s[i] == '\0')
			return 1;

	return 0;
}

int main()
{
	int i, limit=INIT_BUFFER;

	int tube_pere_vers_fils[2];
	int tube_fils_vers_pere[2];

	if(pipe(tube_pere_vers_fils) == -1 || pipe(tube_fils_vers_pere) == -1)
		perror("pipe() cant be created");

	pid_t pid = fork();

	if(pid == -1)
		perror("fork() cant be created");

	if(pid == 0)
	{
		int readed, total_read;

		char *buff, *total_buff;

		close(tube_pere_vers_fils[1]); // 1 pour ecriture
		close(tube_fils_vers_pere[0]); // 0 pour sortie

		// Remarque 1)
		buff = (char *) malloc(sizeof(char) * INIT_BUFFER);

		while(1)
		{
			total_read = 0;

			limit = INIT_BUFFER;

			total_buff = (char *) malloc(sizeof(char) * limit);

			do
			{
				readed = read(tube_pere_vers_fils[0], buff, sizeof(char) * INIT_BUFFER);
				total_read += readed;

				if(total_read > limit-1)
				{
					limit *= 2;
					total_buff = (char *) realloc(total_buff, sizeof(char) * limit);
				}

				total_buff = strcat(total_buff, buff);
			} while(!eof_present(buff, INIT_BUFFER));

			total_buff[total_read] = '\0';

			if(strcmp("quit", total_buff) == 0)
			{
				free(total_buff);
				break;
			}

			for(i=0; i<total_read-1; i++)
			{
				if(total_buff[i] >= 'a' && total_buff[i] <= 'z')
					*(total_buff+i) -= 32;
			}

			write(tube_fils_vers_pere[1], total_buff, sizeof(char) * total_read);

			free(total_buff);
		}

		free(buff);

		close(tube_pere_vers_fils[0]);
		close(tube_fils_vers_pere[1]);

		exit(0);
	} else
	{
		close(tube_pere_vers_fils[0]);
		close(tube_fils_vers_pere[1]);

		char *buff;

		while(1)
		{
			i = 0;

			// Remarque 1)
			buff = lire_clavier(&i);

			// envoie pipe
			write(tube_pere_vers_fils[1], buff, i+1);

			if(strcmp("quit", buff) == 0)
			{
				free(buff);
				break;
			}

			// reception pipe
			read(tube_fils_vers_pere[0], buff, i+1);
			printf("%s\n", buff);

			free(buff);
		}

		close(tube_pere_vers_fils[1]);
		close(tube_fils_vers_pere[0]);
	}

	return 0;
}
