#include "main.h"

/**
 * rev_string - a function used to reverse a string.
 * @str: the input string.
 * Return: nothing.
 */

void rev_string(char *str)
{
	int count = 0, i, j;
	char *str_copy, temp;

	while (count >= 0)
	{
		if (str[count] == '\0')
			break;

		count++;
	}

	str_copy = str;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str_copy + j);
			*(str_copy + j) = *(str_copy + (j - 1));
			*(str_copy + (j - 1)) = temp;
		}
	}
}
