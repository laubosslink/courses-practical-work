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
		close(tube_pere_vers_fils[1]); // 1 pour ecriture
		close(tube_fils_vers_pere[0]); // 0 pour sortie

		pid_t pid_c = fork();

		dup2(tube_pere_vers_fils[0], 0);
		dup2(tube_fils_vers_pere[1], 1);

		int res = execl("./board", "board", "-q", (char *) NULL);

		close(tube_pere_vers_fils[0]);
		close(tube_fils_vers_pere[1]);

		exit(0);
	} else
	{
		close(tube_pere_vers_fils[0]);
		close(tube_fils_vers_pere[1]);

		char c;
		char *buff;

		while(1) {

			i=0;

			printf("shell_board> ");
			buff = lire_clavier(&i);

			// envoie pipe
			write(tube_pere_vers_fils[1], buff, i+1);

			printf("\nBoard says: \"");

			// reception pipe
			while(read(tube_fils_vers_pere[0], &c, sizeof(char)) > 0)
			{
				printf("%c", c);

				if(c == '\n')
					break;
			}

			printf("\"\n");

			free(buff);

			if(strcmp("quit", buff) == 0)
				break;

		}

                close(tube_pere_vers_fils[1]);
                close(tube_fils_vers_pere[0]);
	}

	return 0;
}
