#include "shell.h"
/**
 * _strlen - Prints the string length
 * @str: The string to count
 * Return: The count of characters in a string (str)
 */
int _strlen(char *str)
{
	int i = 0;

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
	char *temp = NULL;
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
		temp = malloc(sizeof(*temp) * _strlen(token));
		if (temp == NULL)
		{
			free(argv);
			print("There is an error", STDOUT_FILENO);
			exit(1);
		}
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
 *
 * Return: Always (0) on success
 */
int main(void)
{
	ssize_t read = 0;
	char *lineptr = NULL;
	size_t n = 0;
	char delim1[1] = " ";
	char delim[1] = "\n";
	char *token = NULL;
	char **argv = NULL;
	pid_t child_pid;
	int wstatus, i = 0;

	while (read != -1)
	{
		print("($) ", STDOUT_FILENO);
		read = getline(&lineptr, &n, stdin);
		if (read == -1)
			break;
		token = strtok(lineptr, delim);
		argv = input_tokenizer(token, delim1);
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("Error");
			}
		}
		else
		{
			wait(&wstatus);
		}
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
		free(lineptr);
	}
	return (0);
}
