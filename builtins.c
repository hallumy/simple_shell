#include "shell.h"

/**
 * exits - Terminates and exits from the shell
 * @lineptr: frees lineptr from main shell
 * Return: Nothing
 */
void exits(char **str, ...)
{
	va_list ap;
	va_start(ap, str);
	free(va_arg(ap, char *));
	va_end(ap);
	if (str != NULL)
	{
		free(str[0]);
		free(str);
	}	
	exit(0);
}

/**
 * check_builtins - checks if a command is a builtin
 * @str: Command input by user
 * @lineptr: frees lineptr from main shell
 * Return: Nothing
 */
void (*check_builtins(char *str))(char **str, ...)
{
	builtin arrbuiltin[] = {
		{"exit", exits},
		{NULL, NULL}
	};
	int i = 0;
	/*va_list ap;

	if (_strcmp(str, "exit") == 0)
	{
		va_start(ap, str);
		free(va_arg(ap, char *));
	}
	va_end(ap);*/

	while (arrbuiltin[i].name != NULL)
	{
		if (_strcmp(str, arrbuiltin[i].name) == 0)
		{
			return arrbuiltin[i].func;
		}
		i++;
	}
	return (0);
}
