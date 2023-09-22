#include "shell.h"
/**
 * hsh - shell loop
 * @info: the parameter
 * @av: the argument vector
 * Return: 0 on success, else 1
 */
int hsh(info_t *info, char **av)
{
	ssize_t input_res = 0;
	int builtin_ret = 0;
	const int BUILTIN_EXIT = -2;
	const int BUILTIN_NOT_FOUND = -1;
	const int BUILTIN_ERROR = -2;
	const int ERR_NO_ERROR = 0;
	const int FREE_INFO_NONE = 0;
	const int FREE_INFO_HISTORY = 1;
	const int INPUT_ERROR = -1;

	while (input_res != INPUT_ERROR && builtin_ret != BUILTIN_EXIT)
	{
		clear_info(info);
		if (interact_shell(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_res = get_input(info);
		if (input_res != INPUT_ERROR)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == BUILTIN_NOT_FOUND)
				find_cmd(info);
		}
		else if (interact_shell(info))
			_putchar('\n');
		free_info(info, FREE_INFO_NONE);
	}
	write_history(info);
	free_info(info, FREE_INFO_HISTORY);
	if (!interact_shell(info) && info->status)
		exit(info->status);
	if (builtin_ret == BUILTIN_ERROR)
	{
		if (info->err_num == ERR_NO_ERROR)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}
/**
 * find_builtin - finds a builtin command
 * @info: the parameter
 * Return: -1 if builtin not found,
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}
/**
 * find_cmd - finds a command
 * @info: the parameter & return info struct
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact_shell(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
/**
 * fork_cmd - forks thread to run cmd
 * @info: the parameter & return info struct
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;
	char *error_msg;

	child_pid = fork();
	if (child_pid == -1)
	{
		error_msg = "Error: Fork failed\n";
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
