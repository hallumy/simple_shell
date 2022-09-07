#include "shell.h"
/**
 * path_handler - Executes commands in PATH
 * @argv: argument vector passed to execve
 * @head_path: address of the linked list containing path directories
 * Return: Nothing
 */
void path_handler(char **argv, node **head_path, node **head_node)
{
	char *list = NULL;
	int i = 0, j = 0, wstatus;
	pid_t path_pid;

	list = strdup(argv[0]);
	while ((*head_path)->dirname[i])
	{
		argv[0][i] = (*head_path)->dirname[i];
		i++;

	}
		argv[0][i++] = '/';
	while (list[j])
	{
		argv[0][i] = list[j];
		i++;
		j++;
	}
	path_pid = fork();
	if (path_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
		/*	printf("2\n");*/
			perror("Error");
		}
	}
	else
	{
		wait(&wstatus);
	/*	printf("We are now freeing path handler\n");*/
		while (argv[i])
		{
			free(argv[i++]);
		}
		free(argv);
		free(list);
		free_pathlist(head_node);
	}
}

/**
 * _strlen - Prints the string length
 * @str: The string to count
 * Return: The count of characters in a string (str)
 */
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
	{
		return (-1);
	}
	while (str[i])
		i++;
	return (i);
}

/**
 * print - writes a character buffer to specified file stream
 * @format: This is the buffer to be written
 * @fd: Specifies the file stream where format is written
 * Return: number of bytes written or -1 on error
 */
int print(char *format, int fd)
{
	return (write(fd, format, _strlen(format)));
}

/**
 * input_tokenizer - Separate commands and their arguments
 * @str: Commandline with optional arguments
 * @delim: Character used to separate the words
 * Return: Nothing
 */
char **input_tokenizer(char *str, char *delim)
{
	int count = 1, j = 0;
	char *token = NULL;
	char *ptr = NULL;
	char **argv = NULL;

	ptr = strdup(str);
	token = strtok(ptr, delim);
	while (token)
	{
		token = strtok(NULL, delim);
		count++;
	}
	argv = malloc(sizeof(*argv) * count);
	if (argv == NULL)
	{
		print("There is an error", STDOUT_FILENO);
		exit(1);
	}
	token = strtok(str, delim);
	while (token)
	{
		argv[j] = _strdup(token);
		j++;
		token = strtok(NULL, delim);
	}
	argv[j] = NULL;
	free(ptr);
	return (argv);
}

/**
 * main - entry point to our shell program
 * @ac: argument counter
 * @av: argument vector
 * Return: Always (0) on success
 */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	ssize_t read = 0;
	char *lineptr = NULL, *token = NULL, **argv = NULL;
	size_t n = 0;
	pid_t child_pid;
	int wstatus, i = 0/*, found*/;
	node *head_path = NULL/*, **head_node = NULL*/;
/*	_path_to_list(&head_path);
	head_path = head_path->next;
	head_node = &head_path;*/
	
	while (read != -1)
	{
		print("($) ", STDOUT_FILENO);
		read = getline(&lineptr, &n, stdin);
		if (read == -1)
			break;
		token = strtok(lineptr, "\n");
		argv = input_tokenizer(token, " ");
		_path_to_list(&head_path);
/*		printf("head path is %s", head_path->dirname);*/
/*		head_path = head_path->next;*/

	/*	head_node = &head_path;*/
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
			/*	printf("found 3 is %d, headpath is %s\n", found, head_path->dirname);
				found = path_finder(argv[0], &head_path);
				printf("found 2 is %d, headpath is %s\n", found, head_path->dirname);
				if (found != 0)
				{
					printf("1, found %d\n", found);
					perror("Error");
				}
				else
				{
					path_handler(argv, &head_path, head_node);
				}*/
			}
		}
		else
		{
			wait(&wstatus);
	/*		printf("we ar now freeing argv\n");*/
			while (argv[i])
			{
				free(argv[i++]);
			}
			free(argv);
		/*	free_pathlist(head_node);*/
			free_list(1, lineptr);
		}
	}
	return (0);
}
