#include "shell.h"
/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	if (dest == src || src == NULL)
	{
		return (dest);
	}

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * _strdup - duplicates string
 * @str: the string to be duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	size_t length = _strlen(str);
	char *duplicate;

	if (str == NULL)
		return (NULL);

	duplicate = malloc(length + 1);
	if (duplicate == NULL)
	{
		return (NULL);
	}

	_strcpy(duplicate, str);
	return (duplicate);
}
/**
 * _puts - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);

		if (str[i] == '\n')
			_putchar(BUF_FLUSH);

		i++;
	}
	_putchar(BUF_FLUSH);
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1 else 0
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE - 1)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}
