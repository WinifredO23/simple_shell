#include "shell.h"
/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		if (info->environ)
		{
			free_string_array(info->environ);
			info->environ = NULL;
		}
		return ((info->environ = list_to_strings(info->env)) ? info->environ : NULL);
	}
	return (info->environ);
}
/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	int env_changed = 0;
	size_t i;
	char *p;
	list_t *current = info->env;

	if (!info->env || !var)
		return (0);
	for (i = 0; current; i++, current = current->next)
	{
		p = starts_with(current->str, var);
		if (p && *p == '=')
		{
			env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			current = info->env;
		}
	}

	info->env_changed = env_changed;
	return (env_changed);
}
/**
 * _setenv - Initialize or modify envrionment
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf;
	size_t buf_len;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = _strdup(var);
	if (!buf)
		return (1);
	buf_len = _strlen(buf) + _strlen(value) + 2;
	buf = _realloc(buf, _strlen(buf), buf_len);
	if (!buf)
	{
		free(buf);
		return (1);
	}
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
