#include "shell.h"
/**
 * _handle_comments - handles comments for simple shell before passing to exec
 * @command: a null terminated 2D array to be executed
 * Return: a pointer to processed string
 */
char **_handle_comments(char **command)
{
	char **tmp;

	for (tmp = command; *tmp != NULL; tmp++)
	{
		if (strncmp(*tmp, "#", 1) == 0)
		{
			*tmp = NULL;
			break;
		}
	}
	return (command);
}

/**
 * _handle_quotes - removes quotes for simple shell before passing to exec
 * @command: a null terminated 2D array to be executed
 * Return: a pointer to processed string
 */
char **_handle_quotes(char **command)
{
	char **tmp, *cpy;
	size_t len;

	tmp = command;
	for (tmp = command; *tmp != NULL; tmp++)
	{
		if ((**tmp == '"' || **tmp == '\'') && (*(*tmp + strlen(*tmp) - 1)
					== '"' || *(*tmp + strlen(*tmp) - 1) == '\''))
		{
			len = strlen(*tmp);
			cpy = (char *)malloc(len - 1);
			if (cpy == NULL)
			{
				perror("quote strdup");
				return (command);
			}
			strncpy(cpy, *tmp + 1, len - 2);
			*tmp = cpy;
		}
		continue;
	}

	return (command);
}


/**
 * strdup_replace - replaces a string with its expanded value
 * @str: the string to be replaced
 * @start: the replacement starts at this index
 * @len: how many characters to be replaced
 * @replacement: the replacement
 * Return: a pointer to the replaced string
 */
char *strdup_replace(const char *str, size_t start, size_t len,
		const char *replacement)
{
	size_t orig_len, repl_len, new_len;
	char *new_str;

	orig_len = strlen(str);
	repl_len = strlen(replacement);
	new_len = orig_len - len + repl_len + 1;
	new_str = (char *)malloc(new_len);
	if (new_str == NULL)
	{
		perror("strdup_replace malloc");
		exit(EXIT_SUCCESS);
	}
	strncpy(new_str, str, start);
	new_str[start] = '\0';
	strcat(new_str, replacement);
	strcat(new_str, str + start + len);

	return (new_str);
}

/**
 * _handle_dollar_sign - handle the $ which accesses env variables
 * @command: a 2D null terminated array to be passed to the simple shell's exec
 * Return: a pointer to the processed command
 */

char **_handle_dollar_sign(char **command)
{
	char **tmp;

	for (tmp = command; *tmp != NULL; tmp++)
	{
		process_dollar_sign(tmp);
	}

	return (command);
}
