#include "shell.h"
/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 */
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE - 1)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
	{
	buf[j++] = c;
	}
	return (1);
}
/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(const char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
	{
		_eputchar(str[i]);
	}
}
/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE - 1)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[j++] = c;
	}
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;
	char buffer[BUFFER_SIZE];
	ssize_t bytes_written;

	if (!str || fd < 0)
	{
		return (-1);
	}

	while (*str)
	{
		if (i >= BUFFER_SIZE)
		{
			bytes_written = write(fd, buffer, i);
			if (bytes_written < 0)
				return (-1);
			i = 0;
		}

		buffer[i++] = *str++;
	}
	if (i > 0)
	{
		bytes_written = write(fd, buffer, i);
		if (bytes_written < 0)
			return (-1);
	}
	return (0);
}

