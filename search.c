#include "shell.h"

/**
 * search - searches through directory for a file
 * @filename: file being searched
 * @dirname: directory where filename is searched for
 * Return: 0 on Success and -1 on failure
 */

int search(char *filename, char *dirname)
{
	int cmp = -1;
	DIR *dirp;
	struct dirent *ptr;

	errno = 0;
	dirp = opendir(dirname);
	if (dirp == NULL)
	{
		perror("Error ctrl d");
		return (-1);
	}
	while ((ptr = readdir(dirp)) != NULL)
	{
		if (ptr->d_type == DT_REG)
		{
			cmp = strcmp(filename, ptr->d_name);
			if (cmp == 0)
			{
				closedir(dirp);
				return (0);
			}
		}
	}
	if (errno != 0)
	{
		closedir(dirp);
		perror("Error ctrl c");
		return (-1);
	}
	closedir(dirp);
	return (-1);
}
/*int main()
{
	char *name = "      ";
	char *dir = ".";
	int i;

	i = search(name, dir);
	printf("The value of i is %d\n", i);
	return (0);
}*/

/**
 * check_apath - Checks if a command is an absolute command path
 * @str: Command to be checked
 * Return: 1 on success -1 on failure
 */
int check_apath(char *str)
{
	int i = 0;
	struct stat statbuf;

	while(str[i])
	{
		if (str[i] == '/')
			break;
		i++;
	}
	if (i == _strlen(str))
		return (0);
	i = stat(str, &statbuf);
	if (i == 0)
		return (1);
	return (0);
}
		
		

