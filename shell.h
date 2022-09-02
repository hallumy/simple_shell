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


char **input_tokenizer(char *str, char *delim);
int print(char *format, int fd);
int _strlen(char *str);
char *_strdup(char *str);


#endif
