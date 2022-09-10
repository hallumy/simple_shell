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
	size_t n = 0;

	if (str == NULL)
	{
		return (NULL);
	}
	else
	{
		size = strlen(str);
		str1 = malloc((sizeof(*str) * size) + 256);
		n = size + 256;
		if (str1 == NULL)
		{
			return (NULL);
		}
		else
		{
			memset(str1, 0,n);
			for (i = 0; i < size; i++)
			{
				str1[i] = str[i];
			}
		}
	}
	return (str1);
}
/**
 * _strlen - function that returns the length of a string
 *
 * @s: string whose length is returned
 *
 * Return: int length of string s
 */
int _strlen(char *s)
{
	int len = 0;
	char cha;
	int count = 1;

	cha = *s;
	while (cha != '\0')
	{
		len++;
		cha = *(s + count);
		count++;
	}

	return (len);
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

	s1_len = strlen(s1);
	s2_len = strlen(s2);
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
/**
 * _strncat - concats 3 strings in a newly allocated memory
 * @first: first string
 * @second: second string
 * @third: Third string
 * Return: pointer to the new string
 */
char *_strncat(char *name, char *sep, char *value)
{
	char *result;
	int l1, l2, l3, i, k;

	l1 = _strlen(name);
	l2 = _strlen(sep);
	l3 = _strlen(value);

	result = malloc(l1 + l2 + l3 + 1);
	if (!result)
		return (NULL);

	for (i = 0; name[i]; i++)
		result[i] = name[i];
	k = i;

	for (i = 0; sep[i]; i++)
		result[k + i] = sep[i];
	k = k + i;

	for (i = 0; value[i]; i++)
		result[k + i] = value[i];
	k = k + i;

	result[k] = '\0';

	return (result);
}
