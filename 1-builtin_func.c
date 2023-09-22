#include "shell.h"

/**
 * _myhistory - Display the command history with line numbers.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unset an alias.
 * @info: Pointer to the info_t structure.
 * @str: The alias string to unset.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *equals_sign, temp_char;
	int ret;

	equals_sign = _strchr(str, '=');
	if (!equals_sign)
		return (1);

	temp_char = *equals_sign;
	*equals_sign = '\0';

	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	*equals_sign = temp_char;
	return (ret);
}

/**
 * set_alias - Set an alias.
 * @info: Pointer to the info_t structure.
 * @str: The alias string to set.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *equals_sign;

	equals_sign = _strchr(str, '=');
	if (!equals_sign)
		return (1);

	if (!*++equals_sign)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias.
 * @node: Pointer to the alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *equals_sign_position = NULL, *alias_name = NULL;

	if (node)
	{
		equals_sign_position = _strchr(node->str, '=');
		for (alias_name = node->str; alias_name <= equals_sign_position; alias_name++)
			_putchar(*alias_name);
		_putchar('\'');
		_puts(equals_sign_position + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - Mimics the alias builtin (man alias).
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *equals_sign_position = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equals_sign_position = _strchr(info->argv[i], '=');
		if (equals_sign_position)
		{
			set_alias(info, info->argv[i]);
		}
		else
		{
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
	}

	return (0);
}

