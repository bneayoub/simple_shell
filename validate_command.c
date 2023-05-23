#include "main.h"
/**
 * validate_command - Checks if the command is a builtin or exists
 * @args: array of command arguments
 *
 * Return: 1 if the command is valid, 0 otherwise
 */
int validate_command(char **args)
{
	if (handle_builtins(args))
	{
		free(args);
		return (0);
	}
	if (!command_exists(args))
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free(args);
		return (0);
	}

	return (1);
}
