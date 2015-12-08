#include <stdio.h> /* printf() */
#include <unistd.h> /* fork(), perror() */
#include <stdlib.h> /* exit() */

int main()
{
	pid_t pid, wait_pid;
	int status;

	pid = fork();


	if(pid == -1)
		perror("fork() can't be created");

	/* I'm child */
	if(pid == 0)
	{
		printf("%d: I'm child !\n", getpid());
		exit(2);
	} else
	{
		printf("%d: I'm father, and i create child with pid '%d'\n", getpid(), pid);
		pause();

		do {

			/* retrieve status of any child  */
			wait_pid = wait(&status);

			if(wait_pid == -1)
			{
				perror("wait() error");
				exit(1);
			}

			/* Check child is ending */
			if(WIFEXITED(status))
				printf("%d: retrieve pid(%d), killed with status %d\n", getpid(), wait_pid, WEXITSTATUS(status));

		} while(!WIFEXITED(status));

		printf("%d: End of father processus.\n", getpid());
		exit(EXIT_SUCCESS);
	}
}
