#include "shell.h"
/**
 * _strdup - allocates new memory that contains a copy of string parameter
 *
 * @str: string to be copied into newly allocated memory
 *
 * Return: a pointer to the newly allcoated memory containing a copy of 'str'
 */
char *_strdup(char *str)
{
	int i, size;
	char *str1;

	if (str == NULL)
	{
		return (NULL);
	}
	else
	{
		size = strlen(str);
		str1 = malloc((sizeof(*str) * size) + 256);
		if (str1 == NULL)
		{
			return (NULL);
		}
		else
		{
			for (i = 0; i < size; i++)
			{
				str1[i] = str[i];
			}
		}
	}
	return (str1);
}
/**
 * _strlen - Prints the string length
 * @str: The string to count
 * Return: The count of characters in a string (str)
 */
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
	{
		return (-1);
	}
	while (str[i])
		i++;
	return (i);
}
/**
 * _strcmp - function that compares two strings
 *
 * @s1: the string that string 'src' is being compared to
 * @s2: the string that is compared to string 'dest'
 *
 * Return: an interger that is respectively less than, equal to or greater than
 * if 'dest' is found to be less than, match or greater than 'src'
 */
int _strcmp(char *s1, char *s2)
{
	int i, s1_len, s2_len, len;
	int comp = 0;

	s1_len = _strlen(s1);
	s2_len = _strlen(s2);
	len = s1_len;
	if (s2_len > s1_len)
		len = s2_len;
	for (i = 0; i < len; i++)
	{
		if (s1[i] - s2[i] == 0)
			continue;
		else
		{
			comp = s1[i] - s2[i];
			break;
		}
	}

	return (comp);
}
