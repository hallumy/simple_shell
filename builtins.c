#include "shell.h"

/**
 * exits - Terminates and exits from the shell
 * Return: Nothing
 */
void exits(char *lineptr)
{
	free(lineptr);
	exit(0);
}

/**
 * check_builtins - checks if a command is a builtin and executes accordingly if it is
 * @str: Command input by user
 * Return: Nothing
 */
void check_builtins(char *str, char *lineptr)
{
	builtin arrbuiltin[] = {
		{"exit", exits},
		{NULL, NULL}
	};
	int i = 0;
	while (arrbuiltin[i].name != NULL)
	{
		if (_strcmp(str, arrbuiltin[i].name) == 0)
		{
		       arrbuiltin[i].func(lineptr);
		}
		i++;
	}
}
/*int main()
{
	char *name = NULL;
	char *lineptr = NULL;
	size_t n = 0;

	printf("before while loop\n");
	while(1)
	{
		printf("Checking builtin\n");
		getline(&lineptr, &n, stdin);
       		name = strtok(lineptr, "\n");
		printf("name is %s\n", name);
		printf("Exiting ....\n");
		check_builtins(name, lineptr);
		printf("No seg fault\n");
	}
	return (0);
}*/
