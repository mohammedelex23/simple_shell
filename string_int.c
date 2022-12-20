#include "shell.h"

/**
 * iscmd - check if file is an executable
 * @filename: filename as char pointer
 *
 * Return: 1 if file is executable, 0 if not
 */
int iscmd(char *filename)
{
	struct stat st;

	stat(filename, &st);
	if ((st.st_mode & S_IFREG) && (!access(filename, X_OK)))
		return (1);
	else
		return (0);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 1 if s1 is greater, -1 if less than s2, 0 if equal
 */

int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}

/**
 * _strlen - returns the length of a string
 * @s: char to check
 * Return: length
 */

int _strlen(char *s)
{
	int count = 0;

	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}
