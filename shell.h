#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ILLNUM 227
#define TOK_DELIM " \t\a"

/**
 * struct cmd - struct to pass different arguments to different functions
 * @argc: number of arguments
 * @argv: commands entered
 * @av: parsed commands
 * @cmd_count: current count of commands entered
 */
typedef struct cmd
{
	int argc;
	char **argv;
	char **av;
	int cmd_count;
} cmd;

/**
 * struct envvar - struct to pass environment information
 * @varname: name of variable
 * @next: next in list
 */
typedef struct envvar
{
	char *varname;
	struct envvar *next;
} envvar_t;

extern char **environ;

envvar_t *add_env_node(envvar_t **head, char *varname);

char *_itoa(int n, char *s);
char *read_line(void);
char **split_line(char *line);
char *str_concat(char *s1, char *s2);
char *_strdup(char *s);
char *_strstr(char *haystack, char *needle);
char *_which(char *filename);
char *_getenv(char *name);

double _atoi(char *s);
int _cd(char *path);
int _error(char **prog, char **av, int cmd_count);
int _execute(char *argv[], char **command, int cmd_count);
int _help(char **args);
int iscmd(char *filename);
int _launch(char **args);
int _putchar(char c);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int word_count(char *s);

void *_calloc(unsigned int nmemb, unsigned int size);
void _env(void);
void free_ptr(char **ptr);
void _loop(void);
void _puts(char *s);
void rm_nl(char **s);
void sigintHandler(int signo);
void exit_handler(char **argv, char **command, int cmd_count, int exit_status);
void ffree(char **pp);

#endif /*__SHELL_H__*/
