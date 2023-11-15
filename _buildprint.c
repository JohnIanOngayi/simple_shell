#include "shell.h"
/**
 * print_list - prints all the elements of a listint list
 * @h: a pointer to the first node of the list
 * Return: the number of nodes
 */
size_t print_list(node *h)
{
	node *ptr;
	size_t num;

	ptr = NULL;
	num = 0;
	ptr = (node *)h;
	while (ptr != NULL)
	{
		num++;
		printf("%s\n", ptr->directory);
		ptr = ptr->next;
	}
	return (num);
}
