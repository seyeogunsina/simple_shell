#include "main.h"

/**
 * _strdup - creates a duplicate of a string in the heap memory.
 * @str: A pointer to a string
 * Return: a pointer to the duplicate string
 */

char *_strdup(const char *str)
{
	char *new_str;
	size_t len_str;

	len_str = _strlen(str);
	new_str = malloc(sizeof(char) * (len_str + 1));

	if (new_str == NULL)
		return (NULL);

	_memcpy(new_str, str, len_str + 1);
	return (new_str);
}

/**
 * _strlen - Returns the length of a string.
 * @str: a pointer to the target string
 * Return: Always 0.
 */

int _strlen(const char *str)
{
	int len_str;

	for (len_str = 0; str[len_str] != 0; len_str++)
		;
	return (len_str);
}


/**
 * cmp_chars - compares the characters of strings
 * @str: input string.
 * @delim: delimiter.
 * Return: 1 if are equals, 0 if not.
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}

	if (i == k)
		return (1);

	return (0);
}


/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 * Return: string splited.
 */

char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		i = _strlen(str);
		str_end = &str[i]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);
	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		/*Replacing delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}


/**
 * _isdigit - checks if an input string is a number
 * @str: input string
 * Return: 1 if string is a number. 0 in other case.
 */

int _isdigit(const char *str)
{
	unsigned int i;

	i = 0;

	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}

	return (1);
}
