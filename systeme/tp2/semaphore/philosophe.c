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

#include <string.h> /* strerror */
#include <errno.h>

#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <sys/shm.h> /* memoire partage */

#include <time.h>

#define ALEA_TIME_LIMIT 2
#define NBR_PHILOSOPHE 5

void p(int id_sem, int number){
	struct sembuf op;
	op.sem_num = number;
	op.sem_op = -1;
	op.sem_flg = 0;

	semop(id_sem, &op, 1);
}

void v(int id_sem, int number){
	struct sembuf op;
	op.sem_num = number;
	op.sem_op = 1;
	op.sem_flg = 0;

	semop(id_sem, &op, 1);
}

char* get_philosophe_values(int id_shm, int id_sem)
{
	p(id_sem, NBR_PHILOSOPHE);

	char *status = (char *) shmat(id_shm, NULL, 0);

        if((void *)status == (void *)-1)
        {
                perror("shmat() doesnt work");
		//fprintf(stderr, ": %s\n", strerror(errno));
                exit(errno);
        }

	v(id_sem, NBR_PHILOSOPHE);

	// @todo optimise les detachements, sinon on en creea chaque get/set ?
	fprintf(stderr, "DEBUG %d\n", status);

	return status;
}

void set_philosophe_value(int id_shm, int id_sem, int philosophe_id, char value)
{
	p(id_sem, NBR_PHILOSOPHE);

	char *status = (char *) shmat(id_shm, NULL, 0);

	if((void *)status == (void *)-1)
	{
                perror("shmat() doesnt work");
		//fprintf(stderr, ": %s\n", strerror(errno));
                exit(errno);
	}

	status[philosophe_id] = value;

	v(id_sem, NBR_PHILOSOPHE);
}

pid_t nouveau_philosophe(int id, int id_sem, int id_shm)
{
	pid_t proc = fork();

	if(proc == -1)
	{
                perror("fork() doesnt work");
		//fprintf(stderr, ": %s\n", strerror(errno));
                exit(errno);
	}

	if(proc == 0)
	{
		while(1)
		{
			// Pense
			set_philosophe_value(id_shm, id_sem, id, 'P');
			printf("[%s] Philosophe %d : Pense\n", get_philosophe_values(id_shm, id_sem), id);
			sleep(rand()%ALEA_TIME_LIMIT);

			// Demande a manger
			set_philosophe_value(id_shm, id_sem, id, 'D');
			printf("[%s] Philosophe %d : Demande a manger\n", get_philosophe_values(id_shm, id_sem), id);
			sleep(rand()%ALEA_TIME_LIMIT);

			// Prend les fourchettes (@todo optimiser, ne prendre qu'une seule fourchette)
			p(id_sem, id);
			printf("[%s] Philosophe %d : Ne peux pas manger\n", get_philosophe_values(id_shm, id_sem), id);
			p(id_sem, (id + NBR_PHILOSOPHE - 1) % NBR_PHILOSOPHE);

			// Mange
			set_philosophe_value(id_shm, id_sem, id, 'M');
			printf("[%s] Philosophe %d : Mange\n", get_philosophe_values(id_shm, id_sem), id);
			sleep(rand()%ALEA_TIME_LIMIT);

			// Rend les fourchettes
			v(id_sem, id);
			v(id_sem, (id + NBR_PHILOSOPHE - 1) % NBR_PHILOSOPHE);
		}

		exit(0);
	}

	return proc;
}

int main(int argc, char *argv[])
{
	int i=0;

	key_t k;
	int id_sem, id_shm;

	k = ftok("philosophe", 'A');

	if(k == -1)
	{
                perror("ftok() doesnt work");
		//fprintf(stderr, ": %s\n", strerror(errno));
                exit(errno);
	}

	// NBR_PHILOSOPHE + 1 (semaphore memoire)
	id_sem = semget(k, NBR_PHILOSOPHE+1, IPC_CREAT | 0600);

	if(id_sem == -1)
	{
                perror("semget() doesnt work");
		//fprintf(stderr, ": %s\n", strerror(errno));
                exit(errno);
	}

	// possibilite d'acces memoire a 1 <=> "singleton"
	semctl(id_sem, NBR_PHILOSOPHE, SETVAL, 1);

	id_shm = shmget(k, sizeof(char *) * NBR_PHILOSOPHE, IPC_CREAT | 0600);

	if(id_shm == -1)
	{
                perror("shmget() doesnt work");
		//fprintf(stderr, ": %s\n", strerror(errno));
                exit(errno);
	}

	// @todo initialiser mem status philo a PPPP..

	srand(time(NULL));

	// Creation des philosophes
	for(; i<NBR_PHILOSOPHE; ++i)
	{
		// une fourchette pour chacun
		semctl(id_sem, i, SETVAL, 1);

		// creation d'un philosophe en l'associant au main (vue comme la table..)
		// on passe en parametre l'id de la memoire partage (actions courrante de chaque philosophe)
		// ainsi que l'id des semaphores (fourchettes, et modification memoire des actions)
		setpgid(nouveau_philosophe(i, id_sem, id_shm), getpid());
	}

	/* '(int*) NULL' is important, could also specify 'int status' var. */
    	while(wait((int*) NULL) != -1); /* wait all childs */

	return EXIT_SUCCESS;
}
