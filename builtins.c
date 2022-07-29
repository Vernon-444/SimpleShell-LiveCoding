#include "SimpleShell.h"

void exitShell(char **arr, char *buffer, int status)
{
	if (arr[2] != NULL && arr[1] != NULL)
	{
		printf("exit error: too many arguments\n");
		return;
	}
	if (arr[1] != NULL)
	{
		status = _atoi(arr[1]);
		if (status < 0)
		{
			printf("exit: '%s' is an invalid exit value\n", arr[1]);
			return;
		}
	}
	free(arr);
	free(buffer);
	fflush(stdin);
	printf("Exiting shell with status[%i]...Thank You!\n", status);
	exit(status);
}
