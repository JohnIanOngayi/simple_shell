#include "shell.h"
/**
 * home - set the first directory the shell is run as the home directory
 * Return: a string to the directory path or NULL
 */
const char *home(void)
{
	char *path;

	path = (char *)malloc(1024 * (sizeof(char)));
	if (path == NULL)
	{
		perror("home_dir");
		return (NULL);
	}
	if ((getcwd(path, 1024)) == NULL)
	{
		perror("get home directory");
		free(path);
		return (NULL);
	}
	return ((const char *)(path));
}
