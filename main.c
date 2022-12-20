#include "shell.h"

/**
 * main - entrypoint to simple_shell
 *
 * @ac: number of arguments
 * @argv: commands and arguments
 *
 * Return: 0 on success
 */
int main(int __attribute__((unused))ac, char *argv[])
{
	size_t n = 0;
	char *lineptr = NULL;
	char **command = NULL;
	int gl = 0, cmd_count = 0, exit_status = 0;

	signal(SIGINT, sigintHandler);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "$ ", 2);
		cmd_count++;
		gl = getline(&lineptr, &n, stdin);
		if (gl < 0)
		{
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			free(lineptr);
			exit(0);
		}
		if (word_count(lineptr) == 0)
			continue;
		command = split_line(lineptr);
		free(lineptr);
		lineptr = NULL;
		if (_strcmp(command[0], "exit") == 0)
		{
			exit_handler(argv, command, cmd_count, exit_status);
			exit_status = 2;
			continue;
		}
		if (_strcmp(command[0], "env") == 0)
		{
			_env();
			ffree(command);
			continue;
		}
		exit_status = _execute(argv, command, cmd_count);
	}
	return (0);
}

/**
 * _execute - executes commands from main function
 * @argv: argument from command line
 * @command: parsed command array
 * @cmd_count: count of commands in session
 * Return: exit status of child
 */
int _execute(char *argv[], char **command, int cmd_count)
{
	pid_t childpid;
	int status, exit_status = 0;
	char *shcmd = command[0];

	childpid = fork();
	if (childpid == -1)
	{
		perror("Child process failed.");
		exit(EXIT_FAILURE);
	}
	if (childpid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (*command[0] != '/')
			command[0] = _which(command[0]);
		if (command[0] == NULL)
			command[0] = shcmd;
		else
			shcmd = NULL;
		if (execve(command[0], command, NULL) < 0)
		{
			if (errno == 2)
			{
				exit_status = _error(argv, &shcmd, cmd_count);
				ffree(command);
				_exit(127);
			}
			ffree(command);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		ffree(command);
		if (WIFEXITED(status))
			WEXITSTATUS(status);
		exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}

/**
 * exit_handler - handles exit
 * @prog: program
 * @command: exit number
 * @cmd_count: current command count
 * @exit_status: status of last command
 */
void exit_handler(char **prog, char **command, int cmd_count, int exit_status)
{
	long int a = 0;

	a = command[1] ? _atoi(command[1]) : 2;
	if (command[1] == NULL)
	{
		ffree(command);
		exit(exit_status);
	}

	if (a > 2147483647 || a < 0)
	{
		errno = 0;
		_error(prog, command, cmd_count);
		ffree(command);
	}
	else
	{
		ffree(command);
		exit(a);
	}
}

/**
 * sigintHandler - handles Ctrl+C
 * @signo: signal to handle
 * Return: void
 */
void sigintHandler(int signo)
{
	signal(SIGINT, sigintHandler);
	(void)signo;
	write(STDERR_FILENO, "\n$ ", 3);
	fflush(stdout);
}
