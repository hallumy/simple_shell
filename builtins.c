#include "shell.h"

/**
 * exits - Terminates and exits from the shell
 * @lineptr: frees lineptr from main shell
 * Return: Nothing
 */
void exits(char **argv)
{
	int i = 0;

	if (argv[i])
		free(argv[i++]);
	if (argv)
		free(argv);
	exit(0);
}

/**
 * check_builtins - checks if a command is a builtin and executes accordingly
 * @str: Command input by user
 * @lineptr: frees lineptr from main shell
 * Return: Nothing
 */
void (*check_builtins(char **argv))(char **argv)
{
	builtin arrbuiltin[] = {
		{"exit", exits},
		{NULL, NULL}
	};
	int i = 0;

	while (arrbuiltin[i].name != NULL)
	{
		if (_strcmp(argv[0], arrbuiltin[i].name) == 0)
		{
			return (arrbuiltin[i].func);
		}
		i++;
	}
	return (0);
}
