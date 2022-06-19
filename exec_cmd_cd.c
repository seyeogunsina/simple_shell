#include "main.h"

/**
 * cd_shell - handles the actual directory change commands
 * @datash: A struct of all relevant environment variables
 * Return: 1 on success
 */

int cd_shell(data_shell *datash)
{
	char *dir;
	int is_home_full, is_home_sym, is_double_dash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		is_home_full = _strcmp("$HOME", dir);
		is_home_sym = _strcmp("~", dir);
		is_double_dash = _strcmp("--", dir);
	}

	if (dir == NULL || !is_home_full || !is_home_sym || !is_double_dash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);
	return (1);
}
