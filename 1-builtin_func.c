#include "shell.h"

/**
 * _myhistory - displays the history list.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	if (info->history == NULL)
	{
		_puts("History is empty or uninitialized.\n");
		return (1);
	}

	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int d;

	p = _strchr(str, '=');
	if (!p)
	{
		_puts("Invalid alias format: Missing '=' character.\n");
		return (1);
	}
	c = *p;
	*p = 0;

	d = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	if (d != 0)
	{
		_puts("Failed to unset alias.\n");
		return (1);
	}

	return (0);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
	{
		_puts("Invalid alias format: Missing '=' character.\n");
		return (1);
	}

	if (!*++p)
	{
		return (unset_alias(info, str));
	}

	unset_alias(info, str);

	if (add_node_end(&(info->alias), str, 0) == NULL)
	{
		_puts("Failed to set alias.\n");
		return (1);
	}

	return (0);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p;

	if (node == NULL)
	{
		_puts("Alias node is NULL\n");
		return (1);
	}

	p = _strchr(node->str, '=');
	if (p != NULL)
	{
		write(1, node->str, p - node->str);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - mimics the man alias
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			if (print_alias(node) != 0)
			{
				_puts("Failed to print alias\n");
			}
			node = node->next;
		}

		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
		{
			if (set_alias(info, info->argv[i]))
			{
				_puts("Failed to set alias\n");
			}
		}
		else
		{
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
	}

	return (0);
}
