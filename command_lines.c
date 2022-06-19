#include "main.h"

/**
 * is_cdir - checks for ":".
 * @path: the path.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */

int is_cdir(char *path, int *ind)
{
	if (path[*ind] == ':')
		return (1);

	while (path[*ind] != ':' && path[*ind])
	{
		*ind += 1;
	}

	if (path[*ind])
		*ind += 1;

	return (0);
}


/**
 * _which - searches for a command and return its location
 * @cmd: the name of the command
 * @_environ: structure containing environment variable
 * Return: location of the command.
 */

char *_which(char *cmd, char **_environ)
{
	char *path, *path_ptr, *path_token, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);

	if (path)
	{
		path_ptr = _strdup(path);
		len_cmd = _strlen(cmd);
		path_token = _strtok(path_ptr, ":");
		i = 0;

		while (path_token != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			
			len_dir = _strlen(path_token);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, path_token);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
													if (stat(dir, &st) == 0)
			{
				free(path_ptr);
				return (dir);
			}
													free(dir);
			path_token = _strtok(NULL, ":");
		}

		free(path_ptr);
		if (stat(cmd, &st) == 0)
			return (cmd);

		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);

	return (NULL);
}


/**
 * is_executable - checks if a command is an executable
 * @datash: data structure
 * Return: 0 if it is not an executable, other number if it is
 */

int is_executable(data_shell *datash)
{
	struct stat st;
	int i;
	char *inp;
	inp = datash->args[0];

	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == '.')
		{
			if (inp[i + 1] == '.')
				return (0);

			if (inp[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (inp[i] == '/' && i != 0)
		{
			if (inp[i + 1] == '.')
				continue;

			i++;
			break;
		}
		else
			break;
	}

	if (i == 0)
		return (0);

	if (stat(inp + i, &st) == 0)
	{
		return (i);
	}

	get_error(datash, 127);
	return (-1);
}


/**
 * check_error_cmd - verifies if user has permissions to access a directory
 * @dir: target directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */

int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}
	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}
	return (0);
}


/**
 * cmd_exec - executes command lines
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */

int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datash);

	if (exec == -1)
		return (1);

	if (exec == 0)
	{
		dir = _which(datash->args[0], datash->_environ);

		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];

		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
