#include "shell.h"
/**
 * _read_line - gets input from stdin
 * Return: a pointer to the string read from stdin or NULL
 */
char *_read_line(void)
{
	char *input;
	size_t n;

	input = NULL;
	n = 0;
	if (_getline(&input, &n, stdin) == -1)
	{
		perror("getline");
		return (NULL);
	}
	return (input);
}
