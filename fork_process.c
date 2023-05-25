#include "main.h"
/**
 * execute_forked_command - Forks a process and executes a command
 * @args: array of command arguments
 * @userInput_buf: buffer holding user input
 *
 * Return: void
 */
int execute_forked_command(char **args, char *userInput_buf)
{
	pid_t pid;
	int status;
	int i;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execute_command(args, userInput_buf) == -1)
		{
			perror(userInput_buf);
			for (i = 0; args[i] != NULL; i++)
			{
				free(args[i]);
			}
			free(args);
			free(userInput_buf);
			exit(EXIT_FAILURE);
		}
	}
	if (wait(&status) == -1)
		perror("wait");
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
