#include "shell.h"
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

	ptr = _strdup(str);
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
	char *lineptr = NULL, *token = NULL, **argv = NULL, *temp = NULL;
	size_t n = 0;
	node *head_path = NULL, **head_node = NULL;

	while (1)
	{
		print("($) ", STDOUT_FILENO);
		read = getline(&lineptr, &n, stdin);
		if (read == -1)
			break;
		token = strtok(lineptr, "\n");
		argv = input_tokenizer(token, " ");
		check_builtins(argv[0], lineptr);
		temp = _path_to_list(&head_path);
		head_node = &head_path;
		process_handler(argv, head_path, head_node, temp);
	}
	if (lineptr)
		free(lineptr);
	return (0);
}
/**
 * process_handler - Handles processes in the shell
 * @argv: Argument vector for execve
 * @head_path: linked list containing PATH directories
 * @head_node: address of head_path head node
 * @temp: address to free in linked list built
 * Return: Nothing
 */
void process_handler(char **argv, node *head_path,
		     node **head_node, char *temp)
{
	int i, wstatus, found;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			found = path_finder(argv[0], &head_path);
			if (found != 0)
			{
				perror("Error");
			}
			else
			{
				path_handler(argv, &head_path);
				exit(0);
			}
		}
	}
	else
	{
		wait(&wstatus);
		i = 0;
		while (argv[i] != NULL)
		{
			if (argv[i])
				free(argv[i++]);
		}
		if (argv)
			free(argv);
		free_pathlist(head_node, temp);
	}
}