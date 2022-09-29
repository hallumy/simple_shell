#include "shell.h"
/**
 * free_argv - frees the argument vector
 * @argv: argument vector
 * Return: Nothing
 */
void free_argv(char **argv)
{

	int i = 0;
	
	while (argv[i] != NULL)
	{
		if (argv[i])
		{
			free(argv[i++]);
		}
	}
	if (argv)
	{
		free(argv);
	}
}
