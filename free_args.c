#include "main.h"
/**
 * free_args - frees memory allocated for command arguments
 * @args: array of command arguments
 *
 * Return: void
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}
