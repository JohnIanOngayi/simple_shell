#include "shell.h"

/**
 * validateArguments - checks the validity of input arguments
 * @name: the key of the environment variable
 * @value: the value to be set to the variable
 * Return: 1 if arguments are valid, 0 otherwise
 */
int validateArguments(const char *name, const char *value)
{
	if (!name || !value || strchr(name, '='))
	{
		fprintf(stderr, "Invalid arguments\n");
		return (0);
	}

	return (1);
}
/**
 * variableExists - checks if an environment variable exists
 * @name: the key of the environment variable
 * @env_var: the environment variable to check
 * @name_len: the length of the key
 * Return: 1 if the variable exists, 0 otherwise
 */
int variableExists(const char *name, const char *env_var, size_t name_len)
{
	return (strncmp(name, env_var, name_len) == 0 && env_var[name_len] == '=');
}

/**
 * updateEnvironmentVariable - updates an existing environment variable
 * @name: the key of the environment variable
 * @value: the value to be set to the variable
 * @env: pointer to the environment variable
 * Return: 0 for success, -1 for failure
 */
int updateEnvironmentVariable(const char *name,
		const char *value, char ***env)
{
	char *new_env;
	size_t new_env_size = (strlen(name) + strlen(value) + 2);

	new_env = malloc(new_env_size);
	if (new_env == NULL)
	{
		perror("malloc");
		return (-1);
	}
	if (snprintf(new_env, new_env_size, "%s=%s", name, value) < 0)
	{
		perror("snprintf");
		free(new_env);
		return (-1);
	}
	free(**env);
	**env = new_env;

	return (0);
}
/**
 * addEnvironmentVariable - adds a new environment variable
 * @name: the key of the environment variable
 * @value: the value to be set to the variable
 * Return: 0 for success, -1 for failure
 */
int addEnvironmentVariable(const char *name, const char *value)
{
	size_t env_size, new_env_size;
	char **new_environ, *new_env;

	env_size = (environ_size() + 2) * sizeof(char *);
	new_environ = realloc(environ, env_size);

	if (!new_environ)
	{
		perror("realloc");
		return (-1);
	}

	free(environ);
	environ = new_environ;
	new_env_size = strlen(name) + strlen(value) + 2;
	new_env = malloc(new_env_size);
	if (new_env == NULL)
	{
		perror("malloc");
		return (-1);
	}
	if (snprintf(new_env, new_env_size, "%s=%s", name, value) < 0)
	{
		perror("snprintf");
		free(new_env);
		return (-1);
	}
	environ[environ_size()] = new_env;
	environ[environ_size() + 1] = NULL;
	return (0);
}
/**
 * environ_size - calculates the size of the environment
 * Return: the size of the environment
 */
size_t environ_size(void)
{
	char **env;
	size_t count = 0;

	for (env = environ; *env != NULL; env++)
		count++;

	return (count);
}
