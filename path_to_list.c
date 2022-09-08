#include "shell.h"

/**
 * _path_to_list - Builds a linked list of path directories
 * @head: head of the newly built linked list
 * Return: node pointer
 */

char *_path_to_list(node **head)
{
	int i = 0;
	char *token = NULL, *dir = NULL, *temp = NULL;
	node *new = NULL, *current = NULL, *first = NULL;

	while (environ[i])
	{
		temp = _strdup(environ[i]);
		token = strtok(temp, "=");
		if (_strcmp(token, "PATH") != 0)
		{
			free(temp);
			i++;
		}
		if (_strcmp(token, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			break;
		}
	}
	first = malloc(sizeof(node));
	if (first == NULL)
	{
		perror("Error");
		exit(1);
	}
	dir = strtok(token, ":");
	first->dirname = dir;
	first->next = NULL;
	current = first;
	while (dir)
	{
		while (current->next)
			current = current->next;
		new = new_node(dir);
		if (new == NULL)
			break;
		current->next = new;
	}
	*head = first;
	return (temp);
}
/**
 * new_node - create a new node
 * @dir: name of directory
 * Return: newly created node
 */
node *new_node(char *dir)
{
	node *new = NULL;

	new = malloc(sizeof(node));
	if (new == NULL)
	{
		perror("Error");
		exit(1);
	}
	dir = strtok(NULL, ":");
	if (dir == NULL)
	{
		free(new);
		return (NULL);
	}
	new->dirname = dir;
	new->next = NULL;
	return (new);
}

/**
 * path_finder - Searches for a file in the PATH directories
 * @file: The file to be searched
 * @head: Linked list of directories in PATH
 * Return: 0 on Success -1 failure
 */
int path_finder(char *file, node **head)
{
	int found;

	while ((*head)->next)
	{
		found = search(file, (*head)->dirname);
		if (found == 0)
		{
			break;
		}
		(*head) = (*head)->next;
	}
	return (found);
}
/**
 * free_pathlist - frees the linked list containing PATH directories
 * @head: Address to the head of this list
 * @tmp: A pointer to be freed
 * Return: Nothing
 */
void free_pathlist(node **head, char *tmp)
{
	node *current = NULL;

	if (head == NULL || *head == NULL)
		return;
	while ((*head)->next)
	{
		current = (*head)->next;
		free(*head);
		*head = current;
	}
	free(*head);
	*head = NULL;
	free(tmp);
}
/**
 * path_handler - Executes commands in PATH
 * @argv: argument vector passed to execve
 * @head_path: address of the linked list containing path directories
 * Return: Nothing
 */
void path_handler(char **argv, node **head_path)
{
	char *list = NULL;
	int i = 0, j = 0, wstatus;
	pid_t path_pid;

	list = _strdup(argv[0]);
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
			perror("Error");
		}
	}
	else
	{
		wait(&wstatus);
		free(list);
	}
}
