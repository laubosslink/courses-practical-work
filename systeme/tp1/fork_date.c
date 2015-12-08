#include <stdio.h> /* printf() */
#include <unistd.h> /* fork(), perror() */
#include <stdlib.h> /* exit() */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	pid_t pid, pid2, wait_pid;
	int i, status;

  // message.log need to exist (rm message.log; touch message.log)
  int fd = open("message.log", O_RDWR);

	pid = fork();

	if(pid == -1)
		perror("fork() can't be created");

	/* I'm child */
	if(pid == 0)
	{
    close(1); // close stdout
    dup(fd); // redirect stdout to fd

		for(i=0; i<10; i++)
		{

			pid2 = fork();

			if(pid2 == 0)
			{
				int res = execl("/bin/date", "date", "-u", (char*) NULL);

        if(res < 0)
				{
					printf("error execl\n");
					exit(res);
				}

        exit(0);
			}

      sleep(3);
		}

    close(fd);
    exit(0); /* really important, else child continue */
	}

	/* father create second child */
	pid2 = fork();

	if(pid2 == -1)
		perror("fork() 2 can't be created");

	/* i'm second child */
	if(pid2 == 0)
	{
    close(1);
    dup(fd);

		for(i=0; i<30; i++)
		{
			printf("Attendre !\n");
      fflush(stdout);
			sleep(2);
		}

    close(fd);
    exit(0);
	}

  /* '(int*) NULL' is important, could also specify 'int status' var. */
  while(wait((int*) NULL) != -1); /* wait all childs */

  printf("C'est terminé!.\n");
}
