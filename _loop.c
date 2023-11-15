#include "shell.h"
/**
 * _loop - keeps the shell runnig infinitely
 */
void _loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		_prompt();
		line = _read_line();
		args = _parser(line, " \t\n\a");
		status = _scratch(args);
		free(line);
		free(args);
	} while (status);
}
