#include "shell.h"
/**
 * _getline -reads a line from standard input stream
 * @n: buffer size to store fetched line
 * @lineptr: An array of strring to store fetched input
 * @stream: stdin
 * Return: Number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t num;

	if (*lineptr == NULL || *n == 0)
	{
		*n = 1024;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			perror("getline malloc");
			return (-1);
		}
	}

	num = read(fileno(stream), *lineptr, *n);
	if (num == -1)
	{
		perror("getline read");
		free(*lineptr);
		return (-1);
	}
	*lineptr = (char *)realloc(*lineptr, num + 1);
	if (*lineptr == NULL)
	{
		perror("getline realloc");
		return (-1);
	}
	(*lineptr)[num] = '\0';

	return (num);
}
