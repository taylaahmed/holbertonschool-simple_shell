#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * execve_wait - forks program into parent and child,
 * having the option to call other functions or wait
 * @path: the path to command/arg
 * @args: the split strings in each index
 * @name: argv[0]
 *
 * Return: status
 */

int execve_wait(char *path, char **args, char *name)
{
	pid_t child_pid;
	int status = 0;

	/* splts into 2 copies */
	child_pid = fork();

	/* fork fails */
	if (child_pid == -1)
	{
		perror(name);
		return (1);
	}

	/* execve */
	else if (child_pid == 0)
	{
		/* pathname, arguments, envioroment */
		if (execve(path, args, environ) == -1)
		{
			perror(name);
			_exit(127);
		}
	}
	/* parent runs wait here */
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (status);
}
