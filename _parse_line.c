#include "shell.h"
/**
 * _parser - fetches the line and stores them in a array of arrays
 * @input: the line fetched from the terminal
 * @delimiter: a string containing the separators
 * Return: an array of strings containing commands to be passed into executor
 */
char **_parser(char *input, const char *delimiter)
{
	char **command, *portion;
	int wcount, i, j;

	wcount = wcounter(input, delimiter);
	command = (char **)malloc((wcount + 1) * sizeof(char *));
	if (command == NULL)
	{
		perror("parser malloc");
		return (NULL);
	}
	i = 0;
	portion = strtok(input, delimiter);
	while (portion != NULL)
	{
		command[i] = strdup(portion);
		if (command[i] == NULL)
		{
			perror("parser strdup");
			for (j = 0; j < i; j++)
				free(command[j]);
			free(command);
			return (NULL);
		}
		i++;
		portion = strtok(NULL, delimiter);
	}
	command[i] = (NULL);
	command = _handle_comments(command);
	command = _handle_quotes(command);
	command = _handle_dollar_sign(command);
	return (command);
}
