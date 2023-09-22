#include "shell.h"
/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string.
 */
int _erratoi(char *s)
{
	int digit;
	int result = 0;
	int sign = 1;

	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}

	while (*s >= '0' && *s <= '9')
	{
		digit = *s - '0';
		if (result > (INT_MAX - digit) / 10)
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		result = result * 10 + digit;
		s++;
	}

	return (result * sign);
}
/**
 * print_error - prints error message
 * @info: the parameter
 * @estr: string
 * Return: 0 if no numbers in string.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs("i: ");
	_eputs(estr);
}
/**
 * print_d - prints a decimal number
 * @input: the iniput
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int count = 0;
	int divisor = 1;
	int digit;

	if (fd == STDERR_FILENO)
	{
		_eputchar('-');
		count++;
		input = -input;
	}
	if (input == 0)
	{
		_putfd('0', fd);
		count++;
	}
	else
	{
		while (divisor <= input / 10)
		{
			divisor *= 10;
		}
		while (divisor > 0)
		{
			digit = input / divisor;
			_putfd('0' + digit, fd);
			count++;
			input %= divisor;
			divisor /= 10;
		}
	}
	return (count);
}
/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[MAX_DIGITS + 1];
	char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef"
				: "0123456789ABCDEF";
	char *ptr = &buffer[MAX_DIGITS];
	unsigned long n = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? -num : num;
	*ptr = '\0';

	if (base < 2 || base > 36)
	{
		return (NULL);
	}
	for (; n != 0; n /= base)
	{
		*--ptr = array[n % base];
	}
	if (num < 0 && !(flags & CONVERT_UNSIGNED))
	{
		*--ptr = '-';
	}
	return (ptr);
}
/**
 * remove_comments - replaces instance of '#' with '\0'
 * @buf: the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}

