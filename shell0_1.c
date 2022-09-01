#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/**
 * main - entry point to our shell program
 *
 * return - Always (0) on success
 */
int main(void)
{
	ssize_t read = 0;
	char *lineptr = NULL;
	size_t n = 0;
	char delim[1] = "\n";
	char *token;
	char **argv;
	extern char **environ;
	pid_t child_pid;
	int wstatus;

	while (read != -1)
	{
		printf("($) ");
		read = getline(&lineptr, &n, stdin);
		token = strtok(lineptr, delim);
		/* argv = malloc(sizeof(token) * _strlen(token)); */
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("Error:");
			}
		}
		else
		{
			wait(&wstatus);
		}
	}
	free(lineptr);
	return (0);
}
