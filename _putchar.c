#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @s: string to print
 * Return: void
 */
void _puts(char *s)
{
	while (*s)
	{
		_putchar(*s);
		s++;
	}
}

/**
 * _env - prints the current environment
 * Return: void
 */
void _env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		_putchar('\n');
		i++;
	}
}

/**
 * _error - prints error
 * @prog: name of program
 * @av: argument
 * @cmd_count: current command count
 * Return: exit status
 */
int _error(char **prog, char **av, int cmd_count)
{
	char *buffer = malloc(sizeof(char) * 10);

	write(STDERR_FILENO, prog[0], _strlen(prog[0]));
	_putchar(':');
	_putchar(' ');
	_puts(_itoa(cmd_count, buffer));
	free(buffer);
	_putchar(':');
	_putchar(' ');

	if (av[0])
	{
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": ", 2);
	}
	if (errno == EACCES)
	{
		write(STDERR_FILENO, av[1], _strlen(av[1]));
		write(STDERR_FILENO, ": Permission Denied\n", 20);
		return (126);
	}
	if (errno == 2)
	{
		write(STDERR_FILENO, "not found\n", 10);
		return (127);
	}
	if (errno == 0)
	{
		write(STDERR_FILENO, "Illegal number", 15);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, av[1], _strlen(av[1]));
		write(STDERR_FILENO, "\n", 1);
		return (2);
	}
	return (2);
}
