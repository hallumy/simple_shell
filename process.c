#include "shell.h"

/**
 * execute - executes a command
 * @argv: array of arguments
 */

void execute(char **argv)
{

	pid_t child_pid;
	int wstatus;
	if (!argv || !argv[0])
	{
		return;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
	}
	if (child_pid == 0)
	{
		execve(argv[0], argv, environ);
			perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	wait(&wstatus);
}
