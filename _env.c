#include "shell.h"
/**
 * _printenv - sets environment variables
 */
void _printenv(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}

/**
 * _getenv - gets an envirnment variable
 * @name: the key of the environment variable
 * Return: a pointer to the value or NULL
 */
char *_getenv(const char *name)
{
	char **env;
	size_t name_len;

	if (!name)
	{
		perror("no name passed");
		return (NULL);
	}

	name_len = strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
			return (*env + name_len + 1);
	}
	return (NULL);
}

/**
 * _printPATH - prints each directory contained in PATH
 */
void _printPATH(void)
{
	char **env, *value, *env_var;

	for (env = environ; *env != NULL; env++)
	{
		if (strncmp("PATH", *env, 5) == 0)
		{
			env_var = strdup(*env);
			if (!env_var)
				exit(EXIT_FAILURE);
			strtok(env_var, "=");
			value = strtok(NULL, ":");
			if (!value)
				exit(EXIT_FAILURE);
			printf("%s\n", value);
			while (value)
			{
				value = strtok(NULL, ":");
				printf("%s\n", value);
			}
			free(env_var);
		}
	}
}

/**
 * _unsetenv - deletes the variable name from the environment
 * @name: the key of the nevironment variable to be deleted
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	char **env, **new_environ;
	size_t name_len, env_size;

	if (!name)
	{
		fprintf(stderr, "Invalid argument\n");
		return (-1);
	}
	name_len = strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
		{
			free(*env);
			while (*(env + 1) != NULL)
			{
				*env = *(env + 1);
				env++;
			}
			*env = NULL;
			env_size = (env - environ + 1) * sizeof(char *);
			new_environ = realloc(environ, env_size);
			if (new_environ == NULL)
			{
				perror("realloc");
				return (-1);
			}
			environ = new_environ;
			return (0);
		}
	}
	return (0);
}

/**
 * _setenv - changes or adds an environment variable
 * @name: the key of the environment variable
 * @value: the value to be set to the variable
 * @overwrite: 1 to overwrite value else 0
 * Return: 0 for success, -1 for failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char **env;
	size_t name_len;

	if (!validateArguments(name, value))
		return (-1);
	name_len = strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		if (variableExists(name, *env, name_len))
		{
			if (overwrite || value)
			{
				if (updateEnvironmentVariable(name, value, &env) == -1)
					return (-1);
			}

			return (0);
		}
	}

	if (addEnvironmentVariable(name, value) == -1)
		return (-1);

	return (0);
}
