#include "shell.h"

/**
 * _path_to_list - Builds a linked list of path directories
 * 
 * Return: node pointer
 */

void _path_to_list(node **head)
{
	int i = 0;
	char *token = NULL, *dir = NULL, *temp = NULL;
	node/* *new = NULL, *current = NULL,*/ *first = NULL;

	while (environ[i])
	{
		temp = strdup(environ[i]);
		token = strtok(temp, "=");
		if (strcmp(token, "PATH") == 0)
		{	
			token = strtok(NULL, "=");
			break;
		}
		i++;
	}
	first = malloc(sizeof(node));
	if (first == NULL)
	{
/*		printf("path 1\n");*/
		perror("Error");
		exit(1);
	}
/*	printf("token is %s\n", token);*/
	dir = strtok(token, ":");
/*	printf("dir before assigning %s\n", dir);*/
	first->dirname = dir;
/*	dir = strtok(token, ":");*/
	first->next = NULL;
/*	current = first;
	while (dir)
	{
		while (current->next)
			current = current->next;
		new = malloc(sizeof(node));
		if (new == NULL)
		{
			printf("path 2\n");
			perror("Error");
			exit(1);
		}
		dir = strtok(NULL, ":");
		if (dir == NULL)
		{
			free(new);
			break;
		}
		new->dirname = dir;
		new->next = NULL;
		current->next = new;
	}*/
	*head = first;
	while (*head)
	{
		printf("dirname is %s\n", (*head)->dirname);
		*head = (*head)->next;
	}
	free(temp);
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
/*		printf("found is %d file is %s dirname is %s\n", found, file, (*head)->dirname);*/
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
 * Return: Nothing
 */
void free_pathlist(node **head)
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
}
/**
 * free_list - will free an n amount of pointers to a string
 * @n: The number of pointers to free
 */
void free_list(int n, ...)
{
	int i;
	char *ptr;
	va_list list;

	va_start(list, n);
	for (i = 0; i < n; i++)
	{
		ptr = va_arg(list, char *);
		if (ptr == NULL)
			ptr = "(nil)";
		free(ptr);
	}
	va_end(list);
}

