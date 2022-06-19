#include "main.h"

/**
 * get_len - Get the length of a number.
 * @n: the input number.
 * Return: Length of the input number.
 */

int get_len(int n)
{
	unsigned int i;
	int length = 1;

	if (n < 0)
	{
		length++;
		i = n * -1;
	}
	else
	{
		i = n;
	}

	while (i > 9)
	{
		length++;
		i = i / 10;
	}

	return (length);
}

/**
 * aux_itoa - a function used to convert an int to string.
 * @n: type int number
 * Return: String.
 */

char *aux_itoa(int n)
{
	unsigned int n1;
	int length = get_len(n);
	char *buff;

	buff = malloc(sizeof(char) * (length + 1));

	if (buff == 0)
		return (NULL);

	*(buff + length) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buff[0] = '-';
	}
	else
	{
		n1 = n;
	}

	length--;
											do {
		*(buff + length) = (n1 % 10) + '0';
		n1 = n1 / 10;
		length--;
	}

	while (n1 > 0)
		;

	return (buff);
}


/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */

int _atoi(char *str)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(str + count) != '\0')
	{
		if (size > 0 && (*(str + count) < '0' || *(str + count) > '9'))
			break;

		if (*(str + count) == '-')
			pn *= -1;

		if ((*(str + count) >= '0') && (*(str + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(str + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
