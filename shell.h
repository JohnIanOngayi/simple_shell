#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <errno.h>
#include <ctype.h>


/*Global Variables*/
extern const char *home_dir;
extern char **environ;
extern int *exit_value;
extern int status;


/**
 * struct node - singli linked list for PATH
 * @directory: a dir in PATH variable
 * @next: address to the next node
 * Description: a lnnked list to help execve fetch paths
 */
typedef struct node
{
	const char *directory;
	struct node *next;
} node;



/*Organ functions to run the simple shell*/
void _loop(void);
int _cd(char **argv);
int _change_directory(char *path, char *current, const char *msg);
int _is_exit(char **argv);
int _is_int(char *str);
int _executor(char **argv);
int _scratch(char **argv);
int lsh_num_builtins(void);
void _prompt(void);
const char *home(void);
node *build_list(void);
char **build_path(char **command, node *h);
size_t print_list(node *h);


/*Functions to handle environment variables*/
void _printenv(void);
void _update_pwd_env(char *current);
int _setenv(const char *name, const char *value, int overwrite);
int validateArguments(const char *name, const char *value);
int variableExists(const char *name, const char *env_var, size_t name_len);
int updateEnvironmentVariable(const char *name,
		const char *value, char ***env);
int addEnvironmentVariable(const char *name, const char *value);
size_t environ_size(void);


/*Functions to get user input*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_read_line(void);
int wcounter(char *str, const char *delimiter);
char **_parser(char *input, const char *delimiter);
char **_handle_comments(char **command);
char **_handle_quotes(char **command);
char **_handle_dollar_sign(char **command);
char *strdup_replace(const char *str, size_t start,
		size_t len, const char *replacement);


/*Functions to process user input*/
void process_dollar_sign(char **cmd);
void replace_generic_env_var(char **cmd, char *pos);
void replace_question_mark(char **cmd, char *pos);
void replace_pid(char **cmd, char *pos);
void replace_env_var(char **cmd, char *pos);


/*Custom functions*/

#endif /*__SHELL_H__*/
