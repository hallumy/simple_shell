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
	node *new = NULL, *current = NULL;

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
	*head = malloc(sizeof(node));
	if (*head == NULL)
	{
/*		printf("path 1\n");*/
		perror("Error");
		exit(1);
	}
/*	printf("token is %s\n", token);*/
	dir = strtok(token, ":");
/*	printf("dir before assigning %s\n", dir);*/
	(*head)->dirname = dir;
/*	dir = strtok(token, ":");*/
	(*head)->next = NULL;
	current = *head;
	while (dir)
	{
		while (current->next)
			current = current->next;
		new = malloc(sizeof(node));
		if (new == NULL)
		{
/*			printf("path 2\n");*/
			perror("Error");
			exit(1);
		}
		dir = strtok(NULL, ":");
		new->dirname = dir;
		new->next = NULL;
		current->next = new;
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
