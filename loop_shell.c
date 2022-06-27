#include "main.h"

/**
 * remove_comments - removes comments from the inputs
 * @inp: the input string
 * Return: the input without comments
 */
char *remove_comments(char *inp)
{
	int i, len;

	len = 0;

	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == '#')
		{
			if (i == 0)
			{
				free(inp);
				return (NULL);
			}

			if (inp[i - 1] == ' ' || inp[i - 1] == '\t' || inp[i - 1] == ';')
				len = i;
		}
	}

	if (len != 0)
	{
		inp = _realloc(inp, i, len + 1);
		inp[len] = '\0';
	}

	return (inp);
}


/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 * Return: no return.
 */

void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;

	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);

		if (i_eof != -1)
		{
			input = remove_comments(input);
			if (input == NULL)
				continue;
			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;														}

			input = rep_var(input, datash);
			loop = split_commands(datash, input);

			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
