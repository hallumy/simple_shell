#include "shell.h"

/**
 * search - searches through directory for a file
 * @filename: file being searched
 * @dirname: directory where filename is searched for
 * Return: 0 on Success and -1 on failure
 */

int search(char *filename, char *dirname)
{
	DIR *dirp;
	struct dirent *ptr;
	
	errno = 0;
	dirp = opendir(dirname);
	if (dirp == NULL)
	{
/*		printf("search2\n");*/
		perror("Error");
		return (-1);
	}
	while ((ptr = readdir(dirp)) != NULL)
	{
		if (ptr->d_type == DT_REG)
		{
			if (strcmp(filename, ptr->d_name) == 0)
				return (0);
		}
	}
	if (errno != 0)
	{
	/*	printf("search1\n");*/
		perror("Error");
		return (-1);
	}
	return (-1);
}
