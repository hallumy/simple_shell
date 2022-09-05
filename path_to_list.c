#include "shell.h"

/**
 * _path_to_list - Builds a linked list of path directories
 * 
 * Return: node pointer
 */

node *_path_to_list(void)
{
	int i = 0;
	char *token, *dir;
	node *head, *new, *current;

	while (environ[i])
	{
		token = strtok(environ[i], "=");
		if (strcmp(token, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			break;
		}
		i++;
	}
	head = malloc(sizeof(node));
	if (head == NULL)
	{
		perror("Error");
		exit(1);
	}
	dir = strtok(token, ":");
	head->dirname = dir;
	head->next = NULL;
	current = head;
	while (dir)
	{
		while (current->next)
			current = current->next;
		new = malloc(sizeof(node));
		if (new == NULL)
		{
			perror("Error");
			exit(1);
		}
		dir = strtok(NULL, ":");
		new->dirname = dir;
		new->next = NULL;
		current->next = new;
	}
	return (head);
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
