#include "shell.h"
/**
 * _path_to_list - Builds a linked list of path directories
 * @head: head of the newly built linked list
 * Return: node pointer
 */

node *_path_to_list(char **temp)
{
	int i = 0, cmp = -1, p = 0;
	char *token = NULL, *dir = NULL;
	node *new = NULL, *current = NULL, *first = NULL;

	while (environ[i])
	{
		*temp = strdup(environ[i]);
		p++;
		token = strtok(*temp, "=");
		cmp = strcmp(token, "PATH");
		if (cmp != 0)
		{
			free(*temp);
			p--;
			i++;
		}
		else
		{
			token = strtok(NULL, "=");
			break;
		}
	}
	first = malloc(sizeof(node));
	p++;
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
		p++;
		if (new == NULL)
		{
			p--;
			break;
		}
		current->next = new;
	}
	return (first);
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
node *path_finder(char *file, int *found, node *head)
{
	while (head->next)
	{
		*found = search(file, head->dirname);
		if (*found == 0)
		{
			break;
		}
		head = head->next;
	}
	return (head);
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
	int p = 0;

	if (head == NULL || *head == NULL)
		return;
	while ((*head)->next)
	{
		current = (*head)->next;
		free(*head);
		p++;
		*head = current;
	}
	free(*head);
	p++;
	*head = NULL;
	free(tmp);
	p++;
}
/**
 * path_handler - Executes commands in PATH
 * @argv: argument vector passed to execve
 * @head_path: address of the linked list containing path directories
 * Return: Nothing
 */
void path_handler(char **argv, node *head_path)
{
	char *list = NULL;
	int i = 0, j = 0, l = 0, wstatus;
	pid_t path_pid;

	list = _strdup(argv[0]);
	l++;
	while (head_path->dirname[i])
	{
		argv[0][i] = head_path->dirname[i];
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
			printf("%s: not found\n", argv[0]);
		}
	}
	else
	{
		wait(&wstatus);
		free(list);
		l--;
	}
}
