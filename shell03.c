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

	while (str[j])
	{
		if (str[j] != ' ')
			break;
		j++;
	}
	if (j == _strlen(str))
	{
		argv = malloc(sizeof(*argv) * (count + 1));
		k++;
		if (argv == NULL)
		{
			exit(1);
		}
		argv[0] = _strdup(str);
		k++;
		argv[1] = NULL;
		return (argv);
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
	char *lineptr = NULL, **argv = NULL, *token = NULL, *temp = NULL, *path;
	size_t n = 0;
	int i = 0, j = 0;
	node *head = NULL;
	void(*func)(char **);

	while (1)
	{
		signal(SIGINT,sig_handler);
		print("", STDOUT_FILENO);
		read = getline(&lineptr, &n, stdin);
		if (read == -1)
			break;
		token = strtok(lineptr, "\n");
		argv = input_tokenizer(token);
		if (!argv || !argv[0])
			execute(argv);
		else
		{
			temp = _path_value("PATH");
			head = build_list(temp);
			path = path_name(argv[0],head);
			func = check_builtins(argv);
			if (func)
			{
				free(lineptr);
				func(argv);
			}
			else if (!path)
			{
				execute(argv);
			}
			else if (path)
			{
				i = 0;
				while (path[i])
				{
					argv[0][i] = path[i];
					i++;
				}
				execute(argv);
			}
	       	}
	}
	i = 0;
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
	}
	free_list(&head);
	if (lineptr)
	{
		free(lineptr);
		j--;
	}
	return (0);
}
