#include "shell.h"

/*A pointer to a string to the home's directory*/
const char *home_dir;
/**
 * main - entry point.
 * @argc: number of command iine arguments
 * @args: a 2D array containing command line arguments
 * @envp: a 2D array containing environment variables
 * Return: status code
 */

int main(int argc, char **args, char **envp)
{
	(void) argc;
	(void) args;
	(void) envp;
	home_dir = home();
	_loop();
	fflush(stdout);
	return (EXIT_SUCCESS);
}
