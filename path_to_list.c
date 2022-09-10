#include "shell.h"
/**
 * _path_value - Builds a linked list of path directories
 * @temp: name of file in path
 * Return: node pointer
 */
char *_path_value(const char *name)
{
	int i, j;
	char *value;

	if (!name)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
	}
	return (0);
}
node *build_list(char *path)
{
	node *head = '\0';
	char *token;
	char *cpath = _strdup(path);

	token = strtok(cpath, ":");
	while (token)
	{
		head = add_node_end(&head, token);
		token = strtok(NULL, ":");
	}

	return (head);
}
/**
 * path_name - build pathname in PATH
 * @filename: command name
 * @head_path: address of the linked list containing path directories
 * Return: Nothing
 */
char *path_name(char *filename, node *head)
{
	struct stat buf;
	char *str;

	node *current = head;

	while (current)
	{
		str = _strncat(current->dirname,"/",filename);
		if (stat(str, &buf) == 0)
		{
			return (str);
		}
		free(str);
		current = current->next;
	}
	return (NULL);
}

/**
 * add_node_end - function that adds a new node at the end of a
 * node list
 * @head: a pointer to a pointer to a list_t type
 * @str: a string to be included in the newly created node
 * Return: address of a head node or NULL on failure
 */
node *add_node_end(node **head, const char *str)
{
	node *new = NULL, *current = NULL;

	new = malloc(sizeof(node));
	if (new == NULL)
	{
		return (NULL);
	}
	new->dirname = strdup(str);
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		current = *head;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
	}
	return (*head);
}
/**
 * free_list - function that frees a list_int
 * list
 *
 * @head:a pointer to  a pointer pointing at the start of the list
 *
 * Return: Nothing
 */
void free_list(node **head)
{
	int j = 0;
	node *current;

	if (head == NULL)
		return;
	while (*head != NULL)
	{
		current = (*head)->next;
		free(*head);
		j++;
		*head = current;
	}
}
