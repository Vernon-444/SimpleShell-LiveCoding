#include "SimpleShell.h"


int checkBuiltins(int status, char **arr, char *buffer)
{
	int i;
	builtin builtins[] = {
		{"env", printEnv},
		{NULL, NULL},
	};

	if (strcmp(arr[0], "exit") == 0)
	{
		exitShell(arr, buffer, status);
		return (1);
	}
	for (i = 0; builtins[i].cmd; i++)
	{
		if (strcmp(arr[0], builtins[i].cmd) == 0)
		{
			builtins[i].func(status);
			return (1);
		}
	}
	return (0);
}

void exitShell(char **arr, char *buffer, int status)
{
	if (arr[2] != NULL && arr[1] != NULL)
	{
		printf("exit error: too many arguments\n");
		return;
	}
	if (arr[1] != NULL)
	{
		status = atoi(arr[1]);
		if (status < 0)
		{
			printf("exit: '%s' is an invalid exit value\n", arr[1]);
			return;
		}
	}
	free(buffer);
	fflush(stdin);
	printf("Exiting shell with status[%i]...Thank You!\n", status);
	exit(status);
}

int printEnv(int status)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(1, environ[i], strlen(environ[i]));
		write(1, "\n", 1);
	}
	return (status);
}
