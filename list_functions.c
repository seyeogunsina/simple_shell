#include "main.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sep_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */

sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new_node, *temp;

	new_node = malloc(sizeof(sep_list));

	if (new_node == NULL)
		return (NULL);

	new_node->separator = sep;
	new_node->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = new_node;
	}

	return (*head);
}


/**
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr_node;

	if (head != NULL)
	{
		curr_node = *head;

		while ((temp = curr_node) != NULL)
		{
			curr_node = curr_node->next;
			free(temp);
		}

		*head = NULL;
	}
}


/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */

line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new_node, *temp;

	new_node = malloc(sizeof(line_list));

	if (new_node == NULL)
		return (NULL);

	new_node->line = line;
	new_node->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}

	return (*head);
}


/**
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr_node;

	if (head != NULL)
	{
		curr_node = *head;

		while ((temp = curr_node) != NULL)
		{
			curr_node = curr_node->next;
			free(temp);
		}
		*head = NULL;
	}
}
