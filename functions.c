#include "shell.h"
/**
 * _strlen - checks the length of a string
 * @s: the string to check
 * Return: integer length of string
 */
size_t _strlen(const char *s)
{
	size_t i = 0;

	if (!s)
	{
		return (0);
	}

	for (; s[i] != '\0'; i++)
		;
	return (i);
}
/**
 * _strcmp - compares two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: pointers s1 - s2
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}
/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of the next character of haystack or NULL
 */
char *starts_with(char *haystack, const char *needle)
{
	if (haystack == NULL || needle == NULL)
	{
		return (NULL);
	}

	while (*needle)
	{
		if (*needle != *haystack)
		{
			return (NULL);
		}
		needle++;
		haystack++;
	}
	return (haystack);
}
/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *destp = dest;

	while (*dest)
	{
		dest++;
	}

	for (; *src; src++, dest++)
	{
		*dest = *src;
	}

	*dest = '\0';
	return (destp);
}
