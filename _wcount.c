#include "shell.h"
/**
 * wcounter - counts number of words in a string
 * @str: the string being evaluated
 * @delimiter: string containing word separators
 * Return: non-negative integer or 0 on sucess, -1 on failure
 */
int wcounter(char *str, const char *delimiter)
{
	int count, in_word, i;

	if (str == NULL || delimiter == NULL)
		return (-1);
	count = 0;
	in_word = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (strchr(delimiter, str[i]) != NULL)
		{
			in_word = 0;
		}
		else
		{
			if (in_word == 0)
			{
				count++;
				in_word = 1;
			}
		}
	}
	return (count);
}
