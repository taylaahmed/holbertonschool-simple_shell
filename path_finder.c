#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char *find_path(char *command)
{
	char *path;
	int i = 0;
	char *path_copy;
	char *directory;
	char *concat;

	path = get_path();
	while (path[i] != '\0')
	{
		i++;
	}

	/* + 1 for \0 */
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

	i = 0;
	directory = strtok(path_copy, ":");
	while (directory != NULL)
	{
		/* + 2 = for / and \0 */
		concat = malloc(strlen(directory) + strlen(command) + 2);

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

char *get_path(void)
{
	char **env;
	int path_length = 5;
	env = environ;

	while (*env != NULL)
	{
		if (strncmp(*env, "PATH=", path_length) == 0)
		{
			return(*env + 5);
		}
		
		env++;
	}
	return (NULL);
}
