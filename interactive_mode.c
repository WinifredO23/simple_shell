#include "shell.h"

/**
 * is_delim - checks if character is a delimeter
 * @c: char to be checked
 * @delim: delimeter
 * Return: if true return 1, else 0
 */
int is_delim(char c, const char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
		{
			return (1);
		}
		delim++;
	}
	return (0);
}

/**
 * _isalpha - checks for alphabet
 * @c: The character to input
 * Return: 1 if c is alphabetic, else 0
 */
int _isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
	{
	return (1);
	}
	else
	{
	return (0);
	}
}
/**
 * interact_shell - checks if shell is in interactive mode
 * @info: address
 * Return: 1 if true, else 0
 */
int interact_shell(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, else return string
 */
int atoii(char *s)
{
	int i;
	int si = 1;
	int f = 0;
	int o;
	int res = 0;

	for (i = 0; s[i] != '\0' && f != 2; i++)
	{
	if (s[i] == '-')
		si *= -1;

	if (s[i] >= '0' && s[i] <= '9')
	{
		f = 1;
		res *= 10;
		res += (s[i] - '0');
	}
	else if (f == 1)
		f = 2;
	}

	o = si * res;
	return (o);
}
