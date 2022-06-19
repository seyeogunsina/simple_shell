#include "main.h"

/**
 * cd_dot - command for changing to the parent directory
 * @datash: struct of relevant data (environ)
 * Return: nothing
 */

void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *copy_pwd, *copy_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	copy_pwd = _strdup(pwd);
	set_env("OLDPWD", copy_pwd, datash);
	dir = datash->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", copy_pwd, datash);
		free(copy_pwd);
		return;
	}
	if (_strcmp("/", copy_pwd) == 0)
	{
		free(copy_pwd);
		return;
	}
	copy_strtok_pwd = copy_pwd;
	rev_string(copy_strtok_pwd);
	copy_strtok_pwd = _strtok(copy_strtok_pwd, "/");
	if (copy_strtok_pwd != NULL)
	{
		copy_strtok_pwd = _strtok(NULL, "\0");
		if (copy_strtok_pwd != NULL)
			rev_string(copy_strtok_pwd);
	}
	if (copy_strtok_pwd != NULL)
	{
		chdir(copy_strtok_pwd);
		set_env("PWD", copy_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(copy_pwd);
}


/**
 * cd_to - It changes from the current to a given directory
 * @datash: A struct of the relevant input data (directories)
 * Return: nothing
 */

void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *copy_pwd, *copy_dir;

	getcwd(pwd, sizeof(pwd));
	dir = datash->args[1];

	if (chdir(dir) == -1)
	{
		get_error(datash, 2);
		return;
	}

	copy_pwd = _strdup(pwd);
	set_env("OLDPWD", copy_pwd, datash);
	copy_dir = _strdup(dir);
	set_env("PWD", copy_dir, datash);
	free(copy_pwd);
	free(copy_dir);
	datash->status = 0;
	chdir(dir);
}


/**
 * cd_previous - It changes from the current to the previous directory
 * @datash: A struct of the relevent data (environ)
 * Return: nothing
 */

void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *present_pwd, *present_oldpwd, *copy_pwd, *copy_oldpwd;

	getcwd(pwd, sizeof(pwd));
	copy_pwd = _strdup(pwd);
	present_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (present_oldpwd == NULL)
		copy_oldpwd = copy_pwd;
	else
		copy_oldpwd = _strdup(present_oldpwd);

	set_env("OLDPWD", copy_pwd, datash);

	if (chdir(copy_oldpwd) == -1)
		set_env("PWD", copy_pwd, datash);
	else
		set_env("PWD", copy_oldpwd, datash);

	present_pwd = _getenv("PWD", datash->_environ);
	write(STDOUT_FILENO, present_pwd, _strlen(present_pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(copy_pwd);

	if (present_oldpwd)
		free(copy_oldpwd);
	datash->status = 0;
	chdir(present_pwd);
}


/**
 * cd_to_home - It is used to change from the current to the home directory
 * @datash: A struct of relevant data (environ)
 * Return: nothinh
 */

void cd_to_home(data_shell *datash)
{
	char *present_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	present_pwd = _strdup(pwd);
	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", present_pwd, datash);
		free(present_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(present_pwd);
		return;
	}

	set_env("OLDPWD", present_pwd, datash);
	set_env("PWD", home, datash);
	free(present_pwd);
	datash->status = 0;
}
