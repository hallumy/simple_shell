#include "shell.h"

/**
 * *_strdup - returns a pointer to a newly allocatedspace witha copy of arg
 * @str: string to copy
 * Return: pointer to array or null
 */
char *_strdup(char *str)
{
	char *strDup = NULL;
	int i, j;

		if (str == NULL)
			return (NULL);
	i = 0;
	while (str[i] != '\0')
		i++;
	strDup = malloc(sizeof(*str) * (256));
	if (strDup == NULL)
		return (NULL);
	j = 0;
	while (str[j] != '\0')
	{
		strDup[j] = str[j];
		j++;
	}
	return (strDup);
}
