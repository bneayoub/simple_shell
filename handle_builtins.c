#include "main.h"
/**
 * handle_builtins - handles the built-in functions
 * @args: arguments array
 * @userInput_buf: user input buffer
 * @exit_num: exit status
 *
 * Return: exit success for exit when successful, and 1 or 0 for env
 */

int handle_builtins(char **args, char *userInput_buf, int exit_num)
{
	char **env;
	int exit_status = EXIT_SUCCESS;
	int i;

	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1])
			exit_status = atoi(args[1]);
		else if (exit_num != -1)
			exit_status = exit_num;
		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
			args[i] = NULL;
		}
		free(args);
		free(userInput_buf);
		exit(exit_status);
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		for (env = environ; *env; ++env)
			printf("%s\n", *env);
		free_args(args);
		return (1);
	}
	return (0);
}
