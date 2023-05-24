#include "main.h"

/**
 * execute_command - execute a given command and checks for erros
 * @args: array of arguments
 * @userInput_buf:user input buffer
 *
 * Return: executed command with success, or exit failure otherwise
 */
int execute_command(char **args, char *userInput_buf)
{
	char *path, *dir;
	char path_search[4096];
	char command_path[4096];

	if (args[0][0] == '/')
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror(userInput_buf);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		path = getenv("PATH");
		if (path == NULL)
		{
			write(2, "PATH variable not found.\n", 25);
			exit(EXIT_FAILURE);
		}

		sprintf(path_search, "%s:/usr/bin", path);

		dir = strtok(path_search, ":");
		while (dir)
		{
			snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);
			if (access(command_path, X_OK) == 0)
			{
				if (execve(command_path, args, NULL) == -1)
				{
					perror(userInput_buf);
					return (EXIT_FAILURE);
				}
			}
			dir = strtok(NULL, ":");
		}
	}
	return (EXIT_SUCCESS);
}
