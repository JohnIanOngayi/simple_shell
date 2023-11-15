#include "shell.h"
/**
 * _prompt - prints the shell prompt
 */
void _prompt(void)
{
	char *current;

	current = NULL;
	current = getcwd(current, 1024);
	if (current == NULL)
	{
		perror("getcwd");
		free(current);
	}
	if (strcmp(home_dir, current) != 0)
	{
		printf("\x1B[31mmyshell%s~$\x1B[0m", current);
		fflush(stdout);
	}
	else
	{
		printf("\x1B[31mmyshell~$\x1B[0m");
		fflush(stdout);
	}
	fflush(stdout);
}
