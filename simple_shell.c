#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * main - reads input and sends calls other functions.
 * @argc: count argument of input
 * @argv: recieving input arguments
 *
 * Return: 0 on sucess
 */

int main(int argc, char **argv)
{
	char *input, **args;
	char *exit_word = "exit";
	int count = 0, status = 0;
	(void)argc;

	signal(SIGINT, SIG_IGN); /* if SIG_IGN, signal is ignored */

	while (1)
	{
		if (isatty(STDIN_FILENO)) /*interactive file */
			printf("($) ");

		input = read_line();
		if (input == NULL)
			exit(status);

		count++;
		args = split_line(input);

		if (args[0] != NULL)
		{
			if (strcmp(input, exit_word) == 0)
			{
				free(args);
				free(input);
				exit(status);
			}

			if (strcmp(args[0], "env") == 0)
			{
				print_enviroment();
				status = 0;
			}
			else
				status = call_path_execve(args, argv[0], count, status);
		}

		free(args);
		free(input);
	}
	return (status);
}

/**
 * call_path_execve - check execute get_path or execve_wait
 * @args: arguments inputed
 * @name: argv[0]
 * @count: number of commands executed in shell
 * @status: exit code
 *
 * Return: status
 */

int call_path_execve(char **args, char *name, int count, int status)
{
	char *path;

	/* checking if input command starts with / */
	if (strchr(args[0], '/') != NULL)
	{
		/* checking if that command is openable and executable */
		if (access(args[0], F_OK | X_OK) == 0)
		{
			status = execve_wait(args[0], args, name);
		}
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n", name, count, args[0]);
			status = 127;
		}
	}
	/* all other inputs that don't start with / */
	else
	{
		path = find_path(args[0]);
		/* if find_path returns executable path */
		if (path != NULL)
		{
			status = execve_wait(path, args, name);
			free(path);
		}
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n", name, count, args[0]);
			status = 127;
		}
	}
	return (status);
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
		return (NULL);
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
