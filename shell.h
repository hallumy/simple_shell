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
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
/**
 * struct node - Node for a linked list
 * @dirname: name of PATH entry
 * @next: pointer to the next node in the list
 */

typedef struct node
{
	char *dirname;
	struct node *next;
} node;

/**
 * struct builtin - Structure containing builtin function definitions
 * @name: The name of the builtin function
 * @func: Pointer to the builtin function
 */
typedef struct builtin
{
	char *name;
	void (*func)(char **);
} builtin;
extern char **environ;

char *_path_value(const char *);
node *build_list(char *);
char *path_name(char *, node *);
node *add_node_end(node **, const char *);
void free_list(node **head);
char **input_tokenizer(char *str);
int print(char *format, int fd);
int _strlen(char *str);
char *_strdup(char *str);
void (*check_builtins(char **))(char **);
void exits(char **);
int _strcmp(char *s1, char *s2);
void execute(char **argv);
char *_strncat(char *name, char *sep, char *value);
#endif
