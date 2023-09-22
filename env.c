#include "shell.h"
/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	list_t *current;

	if (info->env == NULL)
	{
		_puts("Environment variables are empty or uninitialized.\n");
		return (1);
	}
	current = info->env;
	while (current)
	{
		_puts(current->str);
		_putchar('\n');
		current = current->next;
	}
	return (0);
}
/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *n = info->env;
	char *p;

	for (; n != NULL; n = n->next)
	{
		p = starts_with(n->str, name);
		if (p && *p)
			return (p);
	}
	return (NULL);
}
/**
 * _mysetenv - Initialize a new environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Usage: setenv VARIABLE VALUE\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]) != 0)
	{
		
		return (0);
	}

	return (1);
}
/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc < 2)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}

	for (i = 1; i <= info->argc; i++)
	{
		if (_unsetenv(info, info->argv[i]))
		{
			_eputs("Failed to unset environment variable.\n");
			return (1);
		}
	}

	return (0);
}
/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		if (add_node_end(&(info->env), environ[i], 0) == NULL)
		{
			_eputs("Error: Failed to allocate memory for environment list.\n");
			return (1);
		}
	}

	return (0);
}

