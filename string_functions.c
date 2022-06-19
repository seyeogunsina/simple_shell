#include "main.h"

/**
 * _strcat - a function for concatenating two strings
 * @dest: a pointer to the destination string
 * @src: a pointer to the source string
 * Return: apointer to the destination string
 */

char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcpy - A function for copying a string to a destination address.
 * @dest: A pointer to the destination address
 * @src: A pointer to the source string
 * Return: A pointer to the destination address.
 */

char *_strcpy(char *dest, char *src)
{
	size_t i;

	i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - A function used to compare two strings.
 * @str1: a pointer to the first input string
 * @str2: a pointer to the second input strings
 * Return: 0
 */

int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);

	if (str1[i] < str2[i])
		return (-1);

	return (0);
}


/**
 * _strchr - used to search for a character in a string,
 * @str: a pointer to the string.
 * @c: the character to be searched for.
 * Return: the pointer to the first occurrence of the character c.
 */

char *_strchr(char *str, char c)
{
	unsigned int i = 0;

	for (i = 0; *(str + i) != '\0'; i++)
		if (*(str + i) == c)
			return (str + i);

	if (*(str + i) == c)
		return (str + i);

	return ('\0');
}

/**
 * _strspn - A function used to get the length of the substring of a string.
 * @str: a pointer to the target string.
 * @check: a pointer to the string of accepted characters.
 * Return: the number of accepted characters.
 */

int _strspn(char *str, char *check)
{
	int i, j, bool;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(check + j) != '\0'; j++)
		{
			if (*(str + i) == *(check + j))
			{
				bool = 0;
				break;
			}
												}
												if (bool == 1)
			break;
	}
	return (i);
}
