#include "shell.h"

/**
 * check_command - checks if command is an absolute path
 * @argv: Argument vector containing command and arguments
 * Return: 0 on success -1 on failure
 */

int check_command(char **argv)
{
	int i = 0, flag = 1;
	struct stat statbuf;

	printf("check command argv is %s\n", argv[0]);
	while (argv[0][i])
	{
		if (argv[0][i] == '/')
		{
			flag = 0;
			break;
		}
		i++;
	}
	printf("if flag is %d\n", flag);
	if (flag == 0)
	{
		printf("statis %d\n", stat(argv[0], &statbuf));
		if (stat(argv[0], &statbuf) && access(argv[0], X_OK))
		{
			return (0);
		}
	}
	return (-1);
}

/**
 * check_path - Checks if command is in path
 * @argv: Argument vector containing command and arguments
 * Return: 0 on success and -1 on failure
 */

node *check_path(char **argv, node *head_path)
{
	int found = -1;
	node *found_node = NULL;

	found_node = path_finder(argv[0], &found, head_path);
	if (found == 0)
	{
		return (found_node);
	}
	return (NULL);
}

