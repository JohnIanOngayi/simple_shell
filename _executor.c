#include "shell.h"
/**
 * _executor - runs shell built ins
 * @argv: a 2D array containing command line arguments
 * Return: 0 for success
 */
int _executor(char **argv)
{
	pid_t pid;
	pid_t wpid;
	int status;
	node *PATH;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			PATH = build_list();
			argv = build_path(argv, PATH);
			if (execve(argv[0], argv, environ) == -1)
				perror("command not found");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("hsh");
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		(void)wpid;
	}
	return (1);
}
