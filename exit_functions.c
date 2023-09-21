#include "shell.h"
/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the characters to be copied
 * Return: dest
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *dest_p = dest;
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest_p[i] = src[i];
	}
	for (; i < n; i++)
	{
		dest_p[i] = '\0';
	}
	return (dest);
}
/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be used
 * Return: start
 */
char *_strncat(char *dest, char *src, int n)
{
	char *start = dest;

	while (*dest)
		dest++;

	while (*src && n > 0)
	{
		*dest++ = *src++;
		n--;
	}

	*dest = '\0';
	return (start);
}
/**
 * _strchr - finds character in a string
 * @s: the string
 * @c: the character
 * Return: NULL
 */
char *_strchr(char *s, char c)
{
	for (; *s != '\0'; s++)
	{
		if (*s == c)
		return (s);
	}

	return (NULL);
}
