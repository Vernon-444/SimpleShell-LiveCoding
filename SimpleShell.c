#include "SimpleShell.h"

int main(void)
{
	int i, status = EXIT_SUCCESS;
	char *buffer = NULL;
	size_t bytes = 0;

	if (isatty(STDIN_FILENO))
	{
		printf("Welcome to my Shell!\n");
		printf("Please follow each command with the enter key.\n");
	}
	/*Infinate Loop*/
	while(1)
	{
		if (isatty(STDIN_FILENO))
			printf(PROMPT);
		if (getline(&buffer, &bytes, stdin) == EOF)
			break;
		for (i = 0; buffer[i] != '\n'; i++)
		{
			if (buffer[i] != ' ')
			{
				status = findCmd(status, buffer);
				break;
			}
		}
	}
	if(buffer)
		free(buffer);
	return (status);
}
int findCmd(int status, char *buffer)
{
	char *arr[MAX_ARGS], *tok;
	int i = 0, j = 0;
	char delim[] = {' ', '\n'};

	tok = strtok(buffer, delim);
	for (i = 0; tok != NULL; i++)
	{
		arr[i] = tok;
		tok = strtok(NULL, delim);
	}
	arr[i] = NULL;
	if (!checkBuiltins(status, arr, buffer))
		executeCommand(arr, status);
	return (status);
}
int executeCommand(char **cmd, int status)
{
	return (status);
}
