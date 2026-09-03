#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * find_path - gets path and compare to command
 * @command: input by user
 *
 * Return: concated string or NULL
 */

char *find_path(char *command)
{
	char *path_copy, *directory, *concat;

	path_copy = path_copier();

	directory = strtok(path_copy, "=:");
	while (directory != NULL)
	{
		/* + 2 = for / and \0 */
		concat = malloc(strlen(directory) + strlen(command) + 2);
		if (concat == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(concat, directory);
		strcat(concat, "/");
		strcat(concat, command);

		if (access(concat, F_OK | X_OK) == 0)
		{
			free(path_copy);
			return (concat);
		}

		free(concat);
		directory = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * path_copier - creates copy of path to new string
 *
 * Return: NULL or copied string path
 */

char *path_copier(void)
{
	char *path;
	char *path_copy;
	int i = 0;

	path = get_path();

	if (path == NULL || path[i] == '\0')
		return (NULL);

	while (path[i] != '\0')
	{
		i++;
	}

	/* + 1 for \0 */
	path_copy = malloc(i + 1);
	if (path_copy == 0)
	{
		return (NULL);
	}

	i = 0;

	while (path[i] != '\0')
	{
		path_copy[i] = path[i];
		i++;
	}
	path_copy[i] = '\0';

	return (path_copy);
}

/**
 * get_path - recieve path from env
 *
 * Return: path string
 */

char *get_path(void)
{
	char **env;

	env = environ;

	if (env == NULL)
		return (NULL);

	while (*env != NULL)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			return (*env);
		}

		env++;
	}
	return (NULL);
}

/**
 * print_enviroment - printing specific enviroment
 *
 * Return: nothing
 */

void print_enviroment(void)
{
	char **env;
	int i = 0;

	env = environ;

	if (env == NULL)
		return;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
