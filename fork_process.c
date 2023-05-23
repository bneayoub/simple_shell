#include "main.h"
/**
 * execute_forked_command - Forks a process and executes a command
 * @args: array of command arguments
 * @userInput_buf: buffer holding user input
 *
 * Return: void
 */
void execute_forked_command(char **args, char *userInput_buf)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execute_command(args, userInput_buf) == -1)
			perror(userInput_buf);
		exit(EXIT_FAILURE);
	}
	if (wait(&status) == -1)
		perror("wait");
}
