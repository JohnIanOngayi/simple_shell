#include "shell.h"
/**
 * build_list - builds a linked list of the path directories
 * Return: a pointer to the head of the linked list
 */
node *build_list(void)
{
	node *head, *current, *temp, *new_node;
	char *token;
	const char *path;

	head = current = temp = new_node = NULL;
	path = getenv("PATH");
	if (path == NULL)
	{
		perror("getenv");
		return (NULL);
	}
	token = strtok((char *)path, ":");
	if (token == NULL)
	{
		perror("Tokenising");
		return (NULL);
	}
	while (token != NULL)
	{
		new_node = (node *)malloc(sizeof(node));
		if (new_node == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		new_node->directory = strdup(token);
		new_node->next = NULL;
		if (!head)
		{
			head = new_node;
			temp = head;
		}
		else
		{
			temp->next = new_node;
			temp = temp->next;
		}
		token = strtok(NULL, ":");
	}
	return (head);
}
