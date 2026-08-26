#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void find_path(char *command)
{
	char *path;
	int i = 0;
	char *path_copy;
	char *directory;

	path = get_path();
	while (path[i] != '\0')
	{
		i++;
	}

	path_copy = malloc(i + 1);
	if (path_copy == 0)
	{
		printf("failiure");
		exit(1);
	}

	i = 0;

	while (path[i] != '\0')
	{
		path_copy[i] = path[i];
		i++;
	}
	path_copy[i] = '\0';

	directory = strtok(path_copy, ":");
	while (directory != NULL)
	{
		printf("%s", command);

		directory = strtok(NULL, ":");
	}

	return;
}

char *get_path(void)
{
	char **env;

	env = environ;

	while (*env != NULL)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			return(*env + 5);
		}
		
		env++;
	}
	return (NULL);
}


int compare_string(const char *env_path, const char *path)
{
	int i = 0;

	printf("%s\n", path);
	printf("%s\n", env_path);

	/* compare chars one by one */
	while (path[i] != '\0')
	{
		if (env_path[i] != path[i])
		{
			return (0);
		}
		i++;
	}

	/* if other chars after keyword, not correct */
	if (env_path[i] == '\n' || env_path[i] == '\0')
	{
		return (1);
	}

	return (0);
}
