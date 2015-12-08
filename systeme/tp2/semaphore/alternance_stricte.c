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

#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define FATHER_INDICE 0
#define CHILD_INDICE 1

void p(int id, int indice){
	struct sembuf op;
	op.sem_num = indice;
	op.sem_op = -1;
	op.sem_flg = 0;

	semop(id, &op, 1);
}

void v(int id, int indice){
	struct sembuf op;
	op.sem_num = indice;
	op.sem_op = 1;
	op.sem_flg = 0;

	semop(id, &op, 1);
}

int main()
{
	pid_t pid;
	int i;

	key_t k = ftok("alternance_stricte", 'A');
	int id = semget(k, 2, IPC_CREAT | 0600);

	semctl(id, FATHER_INDICE, SETVAL, 1);
	semctl(id, CHILD_INDICE, SETVAL, 0);

	pid = fork();

	if(pid == -1)
		perror("fork() can't be created");

	/* I'm child */
	if(pid == 0)
	{
		for(i=0; i<10; i++)
		{
			p(id, CHILD_INDICE);
			printf("Je suis le processus fils de PID %d\n", getpid());
			v(id, FATHER_INDICE);
		}

		exit(0);
	}

	for(i=0; i<10; i++)
	{
		p(id, FATHER_INDICE);
		printf("Je suis le processus pere de PID %d\n", getpid());
		v(id, CHILD_INDICE);
	}
}
