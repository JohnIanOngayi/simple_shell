#include <ctype.h>
/**
 * _is_int - checks if an array of characters is an integer
 * @str: the string being checked
 * Return: 1 if yes 0 if no
 */
int _is_int(char *str)
{
	while (*str != '\0')
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
