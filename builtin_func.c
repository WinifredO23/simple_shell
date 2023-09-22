#include "shell.h"
/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments.
 * Return: exit status
 */
int _myexit(info_t *info)
{
	const int EXIT_ARG_ERROR = 2;
	const int ERROR = -2;
	int exit_code;

	if (info->argv[1])
	{
		exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = EXIT_ARG_ERROR;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_code;
		return (ERROR);

	}
	info->err_num = -1;
	return (ERROR);
}
/**
 * _mycd - changes the directory
 * @info: Structure containing potential arguments.
 * Return: 0 on success, else 1
 */
int _mycd(info_t *info)
{
	char *direct, buffer[1024];
	char *c = getcwd(buffer, 1024);
	int chdir_d;

	if (!c)
	{
		_puts("getcwd error message\n");
	}

	if (!info->argv[1])
	{
		direct = _getenv(info, "HOME=");
		if (!direct)
		{
			print_error(info, "cd: HOME not set\n");
			return (1);
		}
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		direct = _getenv(info, "OLDPWD=");
		if (!direct)
		{
			print_error(info, "cd: OLDPWD not set\n");
			return (1);
		}
		_puts(direct);
		_putchar('\n');
	}
	else
	{
		direct = info->argv[1];
	}

	chdir_d = chdir(direct);

	if (chdir_d == -1)
	{
		print_error(info, "cd: can't change to ");
		_eputs(direct);
		_eputchar('\n');
		return (1);
	}

	_setenv(info, "OLDPWD", getcwd(buffer, 1024));
	_setenv(info, "PWD", getcwd(buffer, 1024));

	return (0);
}
/**
 * _myhelp - Displays help messages for shell commands.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **message;
	char *help_messages[] = {
		"Usage: help [command]",
		"List available commands or display help for a specific command.",
		"Available commands:",
		"1. cd - Change the current directory",
		"2. ls - List directory contents",
		"3. exit - Exit the shell",
		"4. mkdir - creates directory",
		"5. ls -a - list hidden files",
		NULL
	};

	if (info->argv[1])
	{
		if (_strcmp(info->argv[1], "cd") == 0)
		{
			_puts("cd - Change the current directory\n");
			_puts("Usage: cd [directory]\n");
		}
		else if (_strcmp(info->argv[1], "ls") == 0)
			_puts("ls - List directory contents\n");
		else if (_strcmp(info->argv[1], "exit") == 0)
			_puts("exit - Exit the shell\n");
		else if (_strcmp(info->argv[1], "mkdir") == 0)
			_puts("mkdir - creates directories\n");
		else if (_strcmp(info->argv[1], "ls -a") == 0)
			_puts("ls -a - list hidden files");
		else
		{
			_puts("Help for the specified command is not available.\n");
		}
	}
	else
	{
		message = help_messages;
		while (*message)
		{
			_puts(*message);
			_puts("\n");
			message++;
		}
	}

	return (0);
}

