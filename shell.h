#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

/**
 * struct node - Node for a linked list
 * @dirname: name of PATH entry
 * @next: pointer to the next node in the list
 */

typedef struct node
{
	char *dirname;
	struct node *next;
}node;

extern char **environ;

char **input_tokenizer(char *str, char *delim);
int print(char *format, int fd);
int _strlen(char *str);
char *_strdup(char *str);
int path_finder(char *file, node **head);
int search(char *filename, char *dirname);

#endif
