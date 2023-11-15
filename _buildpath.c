#include "shell.h"
/**
 * build_path - builds a path to an executable file
 * @h: a pointer to the first node of a singly linked list.
 * @command: an array of strings containing the typed command
 * Return: number of elements in the list.
 */

char **build_path(char **command, node *h)
{
	size_t n = 0;
	char *str;

	while (h != NULL)
	{
		if (h->directory == NULL)
		{
			break;
		}
		str = (char *)malloc(strlen(h->directory) + strlen(command[0]) + 2);
		if (str == NULL)
		{
			perror("strdup");
			return (NULL);
		}
		strcpy(str, h->directory);
		strcat(str, "/");
		strcat(str, command[0]);
		if (access(str, X_OK) == 0)
		{
			free(command[0]);
			command[0] = str;
			return (command);
		}
		free(str);
		h = h->next;
		n++;
	}
	return (NULL);
}
