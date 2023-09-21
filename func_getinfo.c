#include "shell.h"
/**
 * clear_info - Initializes info_t struct
 * @info_struct: Struct address
 */
void clear_info(info_t *info_struct)
{
	info_struct->arg = NULL;
	info_struct->argv = NULL;
	info_struct->path = NULL;
	info_struct->argc = 0;
}
/**
 * set_info - Initializes info_t struct
 * @info: Struct address
 * @av: Argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = (char **)malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
			else
			{
				perror("Memory allocation failed");
				exit(EXIT_FAILURE);
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_info - Frees info_t struct fields
 * @info: Struct address
 * @all: True if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;

	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
		{
			free(info->arg);
			info->arg = NULL;
		}
		if (info->env)
		{
			free_list(&(info->env));
			info->env = NULL;
		}
		if (info->history)
		{
			free_list(&(info->history));
			info->history = NULL;
		}

		if (info->alias)
		{
			free_list(&(info->alias));
			info->alias = NULL;
		}
		ffree(info->environ);
		info->environ = NULL;

		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
		{
			close(info->readfd);
		}

		_putchar(BUF_FLUSH);
	}
}

