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
	void (*func)(char **, ...);
} builtin;
extern char **environ;

node *new_node(char *);
char **input_tokenizer(char *str);
int print(char *format, int fd);
int _strlen(char *str);
char *_strdup(char *str);
node *path_finder(char *file, int *, node *head);
int search(char *filename, char *dirname);
node *_path_to_list(char **);
void path_handler(char **argv, node *head_path);
void free_pathlist(node **, char *);
void process_handler(char **argv, int, node*);
int check_apath(char *str);
void (*check_builtins(char *))(char **str, ...);
void free_argv(char **argv);
void exits(char **, ...);
int _strcmp(char *s1, char *s2);
void non_interactive(char **av);
int _putchar(char c);
#endif
