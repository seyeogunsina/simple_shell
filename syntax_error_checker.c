#include "main.h"

/**
 * repeated_char - a function used to count the number of repetitions of a char
 * @inp: the input string
 * @i: index
 * Return: the number of repetitions
 */
int repeated_char(char *inp, int i)
{
	if (*(inp - 1) == *inp)
		return (repeated_char(inp - 1, i + 1));

	return (i);
}


/**
 * error_sep_op - a function for finding syntax errors in the input
 * @inp: the input string
 * @i: index
 * @last: last character read
 * Return: index of error. 0 when there are no
 * errors
 */

int error_sep_op(char *inp, int i, char last)
{
	int cnt;

	cnt = 0;

	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (error_sep_op(inp + 1, i + 1, last));

	if (*inp == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*inp == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			cnt = repeated_char(inp, 0);
													if (cnt == 0 || cnt > 1)
				return (i);
		}
	}

	if (*inp == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			cnt = repeated_char(inp, 0);

			if (cnt == 0 || cnt > 1)
				return (i);
		}
	}

	return (error_sep_op(inp + 1, i + 1, *inp));
}



/**
 * first_char - finds index of the first char
 * @inp: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *inp, int *i)
{
	for (*i = 0; inp[*i]; *i += 1)
	{
		if (inp[*i] == ' ' || inp[*i] == '\t')
			continue;

		if (inp[*i] == ';' || inp[*i] == '|' || inp[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}


/**
 * print_syntax_error - prints when a syntax error is found
 * @datash: data structure
 * @inp: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error(data_shell *datash, char *inp, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (inp[i] == ';')
	{
		if (bool == 0)
			msg = (inp[i + 1] == ';' ? ";;" : ";");
		else
			msg = (inp[i - 1] == ';' ? ";;" : ";");
	}

	if (inp[i] == '|')
		msg = (inp[i + 1] == '|' ? "||" : "|");

	if (inp[i] == '&')
		msg = (inp[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(counter);
		return;									}

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}


/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 * @datash: data structure
 * @inp: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *datash, char *inp)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(inp, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, inp, begin, 0);
		return (1);
	}

	i = error_sep_op(inp + begin, 0, *(inp + begin));
	if (i != 0)
	{
		print_syntax_error(datash, inp, begin + i, 1);
		return (1);
	}

	return (0);
}
