#include "main.h"
/**
 * validate_command - Checks if the command is a builtin or exists
 * @args: array of command arguments
 * @userInput_buf: user input buffer
 * Return: 1 if the command is valid, 0 otherwise
 */
int validate_command(char **args, char *userInput_buf)
{
	if (handle_builtins(args, userInput_buf))
	{
		return (0);
	}
	if (!command_exists(args))
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free_args(args);
		return (0);
	}

	return (1);
}
