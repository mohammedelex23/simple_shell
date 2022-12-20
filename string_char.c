#include "shell.h"

/**
 * word_count - counts words because split_line is bad at arithmetic
 * @s: string to count
 * Return: number of words
 */
int word_count(char *s)
{
	int i;
	int count = 0;
	int state = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			state = 0;
		else if (state == 0)
		{
			state = 1;
			count++;
		}
	}
	return (count);
}


/**
 * split_line - tokenizes input string at spaces
 * @line: string to split
 * Return: pointer to array of split strings
 */
char **split_line(char *line)
{
	int i = 0;
	int bufsize;
	char *token = NULL;
	char **words = NULL;

	rm_nl(&line);

	bufsize = word_count(line);

	words = malloc(sizeof(char *) * (bufsize + 1));

	if (!bufsize)
	{
		ffree(words);
		exit(errno);
	}

	if (!words)
	{
		ffree(words);
		exit(errno);
	}

	token = _strdup(strtok(line, TOK_DELIM));

	while (token)
	{
		words[i] = token;
		i++;
		token = _strdup(strtok(NULL, TOK_DELIM));
	}
	words[i] = NULL;
	return (words);
}


/**
 * str_concat - concatenates two strings
 * @s1: string 1
 * @s2: string 2
 * Return: NULL on failure, or pointer to newly allocated space in memory
 */
char *str_concat(char *s1, char *s2)
{
	unsigned int len1, len2, i, j = 0;
	char *s = NULL;

	if (s1 == NULL)
		len1 = 0;
	else
	{
		for (len1 = 0; s1[len1]; len1++)
			;
	}
	if (s2 == NULL)
		len2 = 0;
	else
	{
		for (len2 = 0; s2[len2]; len2++)
			;
	}

	j = len1 + len2 + 1;

	s = (char *)_calloc(j, sizeof(char));
	if (s == NULL)
		return (NULL);

	for (i = 0; i < len1; i++)
	{
		s[i] = s1[i];
	}
	for (i = 0; i < len2; i++)
	{
		s[i + len1] = s2[i];
	}
	s[len1 + len2] = '\0';
	return (s);
}


/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * @str: string to copy
 * Return: pointer to allocated space
 */
char *_strdup(char *str)
{
	char *result = NULL;
	int len = 0;
	int i = 0;

	if (str == NULL)
		return (NULL);

	while (*(str + i))
		i++;

	len = i;

	result = (char *)_calloc((len + 1), sizeof(char));
	/* result = malloc(sizeof(char) * (len + 1));*/
	if (result == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		*(result + i) = *(str + i);

	return (result);
}


/**
 * _strstr - locates a substring
 * @haystack: string to check
 * @needle: substring to look for
 * Return: pointer to beginning of located substring, or NULL
 */
char *_strstr(char *haystack, char *needle)
{
	while (*haystack)
	{
		char *begin = haystack;
		char *pattern = needle;

		while (*haystack && *pattern && *haystack == *pattern)
		{
			haystack++;
			needle++;
		}
		if (*pattern == '\0')
			return (begin);

		haystack = begin + 1;
	}
	return (NULL);
}
