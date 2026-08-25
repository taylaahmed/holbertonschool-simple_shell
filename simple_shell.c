#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * matches_keyword - copying input string to compare to keyword
 * @input: input word
 * @keyword: word used to compare
 *
 * Return: 1 if success, 0 otherwise
 */
int matches_keyword(const char *input, const char *keyword)
{
	int i = 0;

	/* compare chars one by one */
	while (keyword[i] != '\0')
	{
		if (input[i] != keyword[i])
		{
			return (0);
		}
		i++;
	}

	/* if other chars after keyword, not correct */
	if (input[i] == '\n' || input[i] == '\0')
	{
		return (1);
	}

	return (0);
}

/**
 * main - reads function input and ouputs string
 * @argc: number of arguments
 * @argv: array of strings
 *
 * Return: 1 on sucess, 0 on failure
 */
int main(int argc, char **argv)
{
	char *input;
	ssize_t read = 0;
	size_t size = 0;

	char *exit_word = "exit";

	/* bc first input is $ */
	if (argc > 1)
	{
		exit_word = argv[1];
	}

	printf("($) ");

	/* as long as input is not failure, get line to print */
	read = getline(&input, &size, stdin);
	if (read == -1)
	{
		printf("Error");
		free(input);
		return (0);
	}

	/* call func to see if exit word matches */
	if (matches_keyword(input, exit_word))
	{
		free(input);
		return (0);
	}

	printf("%s", input);

	free(input);

	/* call recursion unless exit */
	main(argc, argv);

	return (1);
}
