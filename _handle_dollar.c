#include "shell.h"
/**
 * process_dollar_sign - process dollar sign in a single command
 * @cmd: a pointer to the command string
 */
void process_dollar_sign(char **cmd)
{
	char *pos;

	while ((pos = strchr(*cmd, '$')) != NULL)
	{
		if (pos[1] == '?')
		{
			replace_question_mark(cmd, pos);
		}
		else if (pos[1] == '$')
		{
			replace_pid(cmd, pos);
		}
		else if (pos[1] == '{')
		{
			replace_env_var(cmd, pos);
		}
		else
		{
			replace_generic_env_var(cmd, pos);
		}

		pos = strchr(pos + 1, '$');
	}
}

/**
 * replace_question_mark - replace $? in the command
 * @cmd: a pointer to the command string
 * @pos: a pointer to the position of the dollar sign
 */
void replace_question_mark(char **cmd, char *pos)
{
	char buffer[32];
	int status = 0;

	snprintf(buffer, sizeof(buffer), "%d", status);
	*cmd = strdup_replace(*cmd, (size_t)(pos - *cmd), 2, buffer);
}

/**
 * replace_pid - replace $$ in the command
 * @cmd: a pointer to the command string
 * @pos: a pointer to the position of the dollar sign
 */
void replace_pid(char **cmd, char *pos)
{
	char buffer[32];

	snprintf(buffer, sizeof(buffer), "%d", getpid());
	*cmd = strdup_replace(*cmd, (size_t)(pos - *cmd), 2, buffer);
}

/**
 * replace_env_var - replace ${VAR} in the command
 * @cmd: a pointer to the command string
 * @pos: a pointer to the position of the dollar sign
 */
void replace_env_var(char **cmd, char *pos)
{
	char *end = strchr(pos + 2, '}');
	char *env_var, *env_value;

	if (end != NULL)
	{
		*end = '\0';
		env_var = strdup(pos + 2);
		if (env_var == NULL)
		{
			perror("handle $ strdup");
			return;
		}

		env_value = getenv(env_var);
		if (env_value != NULL)
		{
			*cmd = strdup_replace(*cmd, (size_t)(pos - *cmd),
					(size_t)(end - pos + 1), env_value);
		}

		free(env_var);
		*end = '}';
	}
}

/**
 * replace_generic_env_var - replace $VAR in the command
 * @cmd: a pointer to the command string
 * @pos: a pointer to the position of the dollar sign
 */
void replace_generic_env_var(char **cmd, char *pos)
{
	char *brace_end, *env_var, *env_value;
	char *end = pos + 1;

	while (*end != ' ' && *end != '\0' && *end != '$' && *end != '{')
	{
		end++;
	}

	if (*end == '{')
	{
		brace_end = strchr(end + 1, '}');
		if (brace_end != NULL)
		{
			*brace_end = '\0';
			env_var = strdup(end + 1);
			*brace_end = '}';
			end = brace_end;
		}
	}
	else
	{
		*end = '\0';
		env_var = strdup(pos + 1);
		*end = ' ';
	}

	if (env_var == NULL)
	{
		perror("handle $ strdup");
		return;
	}

	env_value = getenv(env_var);
	if (env_value != NULL)
	{
		*cmd = strdup_replace(*cmd, (size_t)(pos - *cmd),
				(size_t)(end - pos), env_value);
	}

	free(env_var);
}
