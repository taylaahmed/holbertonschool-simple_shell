#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char *read_line(void);
void looping(void);
char **split_line(char *input);
int execve_wait(char *command, char *name);

int main(void)
{

	looping();

	return (0);
}

void looping(void)
{
	char *input;
	char **args;
	char *name = "./hsh";

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("($) ");
		}

		input = read_line();
		args = split_line(input);
		execve_wait(args[0], name);
	}

	printf("\n");
	exit(EXIT_SUCCESS);
}

char *read_line(void)
{
	char *input = NULL;
	ssize_t read = 0;
	size_t buffer = 0;

	read = getline(&input, &buffer, stdin);
	if (read == -1)
	{
		free(input);
		printf("\n");
		exit(EXIT_SUCCESS);
	}

	return (input);
}

char **split_line(char *input)
{
	int bufsize = 64;
	int position = 0;
	char **array = malloc(bufsize *sizeof(char *));
	char *token;

	if (array == NULL)
	{
		printf("failiure");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, " \n");
	while (token != NULL)
	{
		array[position] = token;
		position++;

		token = strtok(NULL, " \n");
	}

	array[position] = NULL;
	return (array);

}

int execve_wait(char *command, char *name)
{
        pid_t child_pid;
        int status;
        char *args[2];

        args[0] = command; /* eg. /bin/ls */
        args[1] = NULL; /* null terminator */

        /* splts into 2 copies */
        child_pid = fork();

        /* fork fails */
        if (child_pid == -1)
        {
                perror("Error:");
                return (1);
        }
        /* execve */
        else if (child_pid == 0)
        {
                /* pathname, arguments, envioroment */
                if (execve(args[0], args, environ) == -1)
                {
                        perror(name);
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

