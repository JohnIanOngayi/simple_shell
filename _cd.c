#include "shell.h"

/**
 * _update_pwd_env - Updates the environment variables PWD and OLDPWD
 * @current: The current working directory path
 */
void _update_pwd_env(char *current)
{
	if (current == NULL)
		perror("current wd");

	setenv("OLDPWD", current, 1);

	current = getcwd(NULL, 0);

	if (current == NULL)
		perror("current wd");

	setenv("PWD", current, 1);
}

/**
 * _change_directory - Changes the current working directory
 * @path: The target directory path
 * @current: The current working directory path
 * @msg: The error message in case of failure
 * Return: 0 for success, otherwise failure
 */
int _change_directory(char *path, char *current, const char *msg)
{
	if (chdir((char *)path) != 0)
	{
		perror(msg);
		free(current);
		return (0);
	}
	return (1);
}

/**
 * _cd - Implements change directory function
 * @argv: a 2D array containing command line arguments
 * Return: 0 for success, otherwise failure
 */
int _cd(char **argv)
{
	char *path, *current;

	current = getcwd(NULL, 0);
	if (current == NULL)
		perror("current wd");

	if (argv[1] == NULL)
	{
		if (_change_directory((char *)home_dir, current, "arg-less") == 1)
			_update_pwd_env(current);
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		path = strdup(getenv("OLDPWD"));
		if (path != NULL)
		{
			if (_change_directory(path, current, "chdir -") == 1)
				_update_pwd_env(current);
		}
	}
	else
	{
		if (_change_directory(argv[1], current, "chdir arg") == 1)
			_update_pwd_env(current);
	}

	return (1);
}

