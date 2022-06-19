#include "main.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */

r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new_node, *temp;

	new_node = malloc(sizeof(r_var));

	if (new_node == NULL)
		return (NULL);

	new_node->len_var = lvar;
	new_node->val = val;
	new_node->len_val = lval;
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
 * free_rvar_list - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *curr_node;

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
