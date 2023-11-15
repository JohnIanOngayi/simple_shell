#include "shell.h"
/**
 * _scratch - implements functions written from scratch
 * @argv: a 2D array containing command line arguments
 * Return: 0 for success
 */
int _scratch(char **argv)
{
	char *builtin_str[] = {
		"cd",
		"exit"
	};
	int (*builtin_func[]) (char **) = {
		&_cd,
		&_is_exit
	};
	int i, j;

	j = (sizeof(builtin_str) / sizeof(char *));

	if (argv[0] == NULL)
		return (1);
	for (i = 0; i < j; i++)
	{
		if (strcmp(argv[0], builtin_str[i]) == 0)
			return ((*builtin_func[i])(argv));
		if (strcmp(argv[0], "env") == 0)
			_printenv();
	}
	return (_executor(argv));
}
