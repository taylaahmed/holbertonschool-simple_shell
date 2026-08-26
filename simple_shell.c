#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - reads input and sends calls other functions.
 *
 * Return: 0 on sucess
 */

int main(void)
{
	char *input;
	char **args;

	/* continue while not 0 */
	while (1)
	{
		/* checks if interactive file */
		if (isatty(STDIN_FILENO))
			printf("($) ");

		/* call functions */
		input = read_line();
		args = split_line(input);
		find_path(args[0]);

		/* check if command is empty string/null, call execve func */
		if (args[0] != NULL)
			execve_wait(args);

		free(args);
		free(input);
	}
	/* exit sucessful */
	exit(0);

	return (0);
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
		exit(0);
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

	/* malloc size of buffer */
	char **array = malloc(buf_size * sizeof(char *));

	/* separate word */
	char *token;

	if (array == NULL)
	{
		printf("failiure");
		exit(1); /* exit failure */
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

int execve_wait(char **args)
{
	pid_t child_pid;
	int status;

	/* splts into 2 copies */
	child_pid = fork();

	/* fork fails */
	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}

	/* execve */
	else if (child_pid == 0)
	{
		/* pathname, arguments, enviroment */
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			exit(1);
		}
	}

	/* parent runs wait here */
	else
	{
		wait(&status);
	}
	return (0);
}
