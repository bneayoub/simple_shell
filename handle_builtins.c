#include "main.h"
/**
 * handle_builtins - handles the built-in functions
 * @args: arguments array
 * @userInput_buf: user input buffer
 *
 * Return: exit success for exit when successful, and 1 or 0 for env
 */

int handle_builtins(char **args, char *userInput_buf)
{
	char **env;
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
			args[i] = NULL;
		}
		free(args);
		free(userInput_buf);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		for (env = environ; *env; ++env)
			printf("%s\n", *env);
		free_args(args);
		return (1);
	}
	return (0);
}
