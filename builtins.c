#include "shell.h"

/**
 * exits - Terminates and exits from the shell
 * @lineptr: frees lineptr from main shell
 * Return: Nothing
 */
void exits(char *lineptr)
{
	free(lineptr);
	exit(0);
}

/**
 * check_builtins - checks if a command is a builtin and executes accordingly
 * @str: Command input by user
 * @lineptr: frees lineptr from main shell
 * Return: Nothing
 */
int check_builtins(char *str)
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
			/*arrbuiltin[i].func(lineptr);*/
			return (0);
		}
		i++;
	}
	return (-1);
}
/**
 * call_builtins - executes a builtin command
 * @str: Command input by user
 * @lineptr: frees lineptr from main shell
 * Return: Nothing
 */
void call_builtins(char *str, char *lineptr)
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
