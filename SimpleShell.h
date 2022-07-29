#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define PROMPT "SimpleShell: "
#define MAX_ARGS 32

extern char **environ;

typedef struct builtin_struct
{
	char *cmd;
	int (*func)(int status);
} builtin;

int findCmd(int status, char *buffer);
char *searchCmd(char *filename);
char *findPath();
int executeCommand(char **cmd, int status);
/*builtins*/
int checkBuiltins(int status, char **arr, char *buffer);
void exitShell(char **arr, char *buffer, int status);
int printEnv(int status);
int clearTerm(int status);

#endif
