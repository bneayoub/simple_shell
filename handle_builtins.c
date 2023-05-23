#include "main.h"
/**
 * handle_builtins - handles the built-in functions
 * @args: arguments array
 *
 * Return: exit success for exit when successful, and 1 or 0 for env
 */

int handle_builtins(char **args)
{
	char **env;

	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		for (env = environ; *env; ++env)
			printf("%s\n", *env);
		return (1);
	}
	return (0);
}
