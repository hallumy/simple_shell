#include "shell.h"
/**
 * print - writes a character buffer to specified file stream
 * @format: This is the buffer to be written
 * @fd: Specifies the file stream where format is written
 * Return: number of bytes written or -1 on error
 */
void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		print("\n",STDIN_FILENO);
	}
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
char **input_tokenizer(char *str)
{
	int count = 1, j = 0;
	char *token = NULL;
	char *ptr = NULL;
	char **argv = NULL;

	while (str[j])
	{
		if (str[j] != ' ')
			break;
		j++;
	}
	if (j == _strlen(str))
	{
		argv = malloc(sizeof(*argv) * (count + 1));
		if (argv == NULL)
		{
			print("There is an error", STDOUT_FILENO);
			exit(1);
		}
		argv[0] = _strdup(str);
		argv[1] = NULL;
		return (argv);
	}
	else
	{
		ptr = _strdup(str);
		token = strtok(ptr, " ");
		while (token)
		{	
			token = strtok(NULL, " ");
			count++;
		}
		argv = malloc(sizeof(*argv) * count);
		if (argv == NULL)
		{
			print("There is an error", STDOUT_FILENO);
			exit(1);
		}
		token = strtok(str, " ");
		j = 0;
		while (token)
		{
			argv[j] = NULL;
			argv[j] = _strdup(token);
			j++;
			token = strtok(NULL, " ");
		}
		argv[j] = NULL;
		free(ptr);
		return (argv);
	}
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
	char *lineptr = NULL, **argv = NULL, *token = NULL, *temp = NULL;
	size_t n = 0;
	node *head_path = NULL, **head_node = NULL;

	while (1)
	{
		signal(SIGINT,sig_handler);
		print("", STDOUT_FILENO);
		read = getline(&lineptr, &n, stdin);
		if (read == -1)
			break;
		token = strtok(lineptr, "\n");
		argv = input_tokenizer(token);
		/*check_builtins(argv[0], lineptr);*/
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
	int i = 0, wstatus = 0, found = 1;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			found = path_finder(argv[0], &head_path);
			if (found != 0)
			{
			/*	printf("%s: not found\n", argv[0]);*/
				exit(0);
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
/**
 * non_interactive - Handles shell in non interactive
 * @av: Argument vector for execve
 * Return: Nothing
 */
void non_interactive(char **av)
{
	int wstatus, i = 0;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		if(execve(av[0], av, environ) == -1)
		{
			perror("Error");
		}
	}
	else
	{
		wait(&wstatus);
		i = 0;
		while (av[i] != NULL)
		{
			if (av[i])
				free(av[i++]);
		}
		if (av)
			free(av);
	}
}
