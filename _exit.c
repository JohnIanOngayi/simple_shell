#include "shell.h"
/**
 * _is_exit - implements the exit function
 * @argv: a 2D array containing command line arguments
 * Return: the exit value or 0 for success
 */

int _is_exit(char **argv)
{
	int *exit_value;
	int is_digit;

	exit_value = (int *)malloc(sizeof(int));
	if (exit_value == NULL)
	{
		perror("exit_int malloc");
	}
	*exit_value = 0;
	if (argv[1] != NULL)
	{
		perror("too many arguments");
		*exit_value = 1;
		_loop();
	}
	if (!argv[1])
		exit(EXIT_SUCCESS);
	if (argv[1])
	{
		is_digit = _is_int(argv[1]);
		if (is_digit == 1)
		{
			*exit_value = atoi(argv[1]);
			exit(*exit_value);
		}
		else
			perror("no numeric argument provided");
	}
	return (0);
}
