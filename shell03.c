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
	int count = 1, j = 0, k = 0;
	char *token = NULL;
	char *ptr = NULL;
	char **argv = NULL;

	if (str == NULL)
	{
		return NULL;
	}
	while (str[j])
	{
		if (str[j] != ' ')
			break;
		j++;
	}
	if (j == _strlen(str))
	{
		return (argv);
		printf("argv is %s\n", argv[0]);
	}
	else
	{
		ptr = _strdup(str);
		k++;
		token = strtok(ptr, " ");
		while (token)
		{	
			token = strtok(NULL, " ");
			count++;
		}
		argv = malloc(sizeof(*argv) * count);
		k++;
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
			k++;
			j++;
			token = strtok(NULL, " ");
		}
		argv[j] = NULL;
		free(ptr);
		k--;
	/*	printf("k malloced is %d\n", k);*/
		return (argv);

	}
}

/**
 * main - entry point to our shell program
 * @ac: argument counter
 * @av: argument vector
 * Return: Always (0) on success
 */
int main(int ac, char **av)
{
	ssize_t read = 0;
	char *lineptr = NULL, **argv = NULL, *token = NULL, *temp = NULL;
	size_t n = 0;
	int j = 0, found = -1, status = 0;
	node *head_path = NULL, **head_node = NULL, *found_node = NULL;
	void (*built)(char **, ...);

/*	head_path = _path_to_list(&temp);
        head_node = &head_path;*/


	while (1)
	{
		signal(SIGINT,sig_handler);
		print("", STDOUT_FILENO);
		read = getline(&lineptr, &n, stdin);
		j++;
		if (read == -1)
			break;
		token = strtok(lineptr, "\n");
		argv = input_tokenizer(token);
		if (argv == NULL)
		{
			continue;
		}
		built = check_builtins(argv[0]);
		if (built)
		{
			built(argv, lineptr);
		}
		head_path = _path_to_list(&temp);
                head_node = &head_path;
		found_node = path_finder(argv[0], &found, head_path);
		if (found == 0)
		{	
			path_handler(argv, found_node);
		
		}
		else if (check_apath(argv[0]))
		{
			process_handler(argv);
		}
		else
		{

			j = 0;
			while (av[0][j])
                                {
                                        write(STDERR_FILENO, &(av[0][j++]), 1);
                                }
			print(": ", STDERR_FILENO);
			_putchar(ac + '0');
			print(": ", STDERR_FILENO);
			j = 0;
			while (argv[0][j])
                                {
                                        write(STDERR_FILENO, &(argv[0][j++]), 1);
                                }
			print(": not found\n", STDERR_FILENO);
			status = 127;
		}
		free_pathlist(head_node, temp);
		free_argv(argv);
		/*i = 0;
		while (argv[i] != NULL)
        	{
                	if (argv[i])
                	{
                        	free(argv[i++]);
                        	j++;
                	}
        	}
        	if (argv)
        	{
                	free(argv);
                	j++;
        	}	*/


	}
	if (lineptr)
	{
		free(lineptr);
		j--;
	}
	if (head_node)
	{
		free_pathlist(head_node, temp);
	}
	return (status);

}

		
/**
 * process_handler - Handles processes in the shell
 * @argv: Argument vector for execve
 * Return: Nothing
 */
void process_handler(char **argv)
{
	int/* i = 0, j = 0,*/ wstatus = 0;
	pid_t ppid;

	ppid = fork();
	if (ppid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			exit(1);
		}
	}
	else 
	{
		wait(&wstatus);
	}
}
