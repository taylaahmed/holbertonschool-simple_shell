#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * main - reads input and sends calls other functions.
 *
 * Return: 0 on sucess
 */

int main(int argc, char **argv)
{
	char *input, **args, *path;
	char *exit_word = "exit";
	int compare;
	int count = 0;

	(void)argc;

	/* if SIG_IGN, then signal is ignored */
	signal(SIGINT, SIG_IGN);

	while (1)
	{
		/* checks if interactive file */
		if (isatty(STDIN_FILENO))
			printf("($) ");

		input = read_line();

		if (input == NULL)
			exit(127);

		count++;
		args = split_line(input);
	

		compare = strcmp(input, exit_word);
		if (compare == 0)
		{
			free(args);
			free(input);
			exit(count);
		}

		if (args[0] != NULL)
		{
			if (access(args[0], F_OK | X_OK) == 0)
			{
				execve_wait(args[0], args, argv[0]);
			}
			else
			{
			path = find_path(args[0]);
				if (path != NULL)
				{
					execve_wait(path, args, argv[0]);
					free(path);
				}
				else
				{
	 				fprintf(stderr, "%s: %d: %s: not found\n", argv[0], count, args[0]);
					free(path);
				}
			}
		}
		free(args);
		free(input);
	}
	exit(127);
	return (127);
}

/**
 * read_line - reads input and checks for end of file command
 *
 * Return: input
 */

char *read_line(void)
{
	char *input = NULL;
	ssize_t read = 0;
	size_t buffer = 0;

	read = getline(&input, &buffer, stdin);

	/* if end of file, ctrl D */
	if (read == -1)
	{
		free(input);
		return(NULL);
	}

	return (input);
}

/**
 * split_line - splits input lines into seperate strings
 * @input: input line
 *
 * Return: the new array of split strings
 */
char **split_line(char *input)
{
	int buf_size = 64;
	int index = 0;
	char **array;
	char *token;

	/* malloc size of buffer */
	array = malloc(buf_size * sizeof(char *));

	if (array == NULL)
	{
		printf("failiure");
		exit(127); /* exit failure */
	}

	/* splits input from new line/space */
	token = strtok(input, " \n");

	/* putting token name into correct index */
	while (token != NULL)
	{
		array[index] = token;
		index++;

		/* pick up where left off in same line */
		token = strtok(NULL, " \n");
	}

	/* add null at end of array */
	array[index] = NULL;
	return (array);

}

/**
 * execve_wait - forks program into parent and child,
 * having the option to call other functions or wait
 * @args: the split strings in each index
 *
 * Return: 0 on sucess
 */

int execve_wait(char *path, char **args, char *name)
{
	pid_t child_pid;
	int status;

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
			exit(127);
		}
	}

	/* parent runs wait here */
	else
	{
		wait(&status);
	}
	return (0);
}
