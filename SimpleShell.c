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
	int i = 0, isPathCmd = 0;
	char *cmd, delim[] = {' ', '\n'};

	tok = strtok(buffer, delim);
	for (i = 0; tok != NULL; i++)
	{
		arr[i] = tok;
		tok = strtok(NULL, delim);
	}
	arr[i] = NULL;
	if (!checkBuiltins(status, arr, buffer))
	{
		cmd = searchCmd(arr[0]);
		if (!cmd)
		{
			return(status);
		}
		if (strcmp(cmd, arr[0]) != 0)
		{
			arr[0] = cmd;
			isPathCmd = 1;
		}
		status = executeCommand(arr, status);
		// if (isPathCmd)
		// 	free(arr[0]);
	}
	return (status);
}

char *searchCmd(char *filename)
{
	char *cmd = NULL, *path, *tmp, *dir, *temp;
	struct stat st;
	int fileExists = 0;

	if (stat(filename, &st) == 0)
	{
		printf("File found\n");
		fileExists = 1;
		if (access(filename, X_OK) == 0)
			return (filename);
	}
	path = findPath();
	dir = strtok(path, "=");
	dir = strtok(NULL, ":\n");
	while (dir)
	{
		dir = strdup(dir);
		tmp = strcat(dir, "/");
		printf("%s\n", tmp);
		cmd = strcat(tmp, filename);
		printf("%s\n", cmd);
		if (stat(cmd, &st) == 0)
		{
			printf("File found\n");
			fileExists = 1;
			if (access(cmd, X_OK) == 0)
			{
				// free(path);
				return (cmd);
			}
		}
		dir = strtok(NULL, ":\n");
	}
	printf("%s\n", cmd);
	perror("Cmd not found");
		return (NULL);
	free(path);
	return (cmd);
}

char *findPath()
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH", 4) == 0)
		{
			printf("%s\n", environ[i]);
			return (strdup(environ[i]));
		}
	}
	return (NULL);
}

int executeCommand(char **cmd, int status)
{
	pid_t checkProcess;

	checkProcess = fork();
	if (checkProcess < 0)
	{
		perror("Could not create child process");
		return (status);
	}
	if (checkProcess == 0)
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("Command could not execute");
	}
	else
	{
		wait(&status);
		status = WEXITSTATUS(status);
	}
	return (status);
}
