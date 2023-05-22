#include "main.h"

/**
 * main - our main shell function
 * Return: 0 on success
 */

int main(void)
{
	char *userInput_buf = NULL;
	size_t size_buf = 0;
	ssize_t readNO;
	char **args = NULL;
	pid_t pid;
	int status = 0;
	char *tok;
	int i = 1;
	char *path;
	char *dir;
	char path_search[4096];
	int is_interactive = isatty(STDIN_FILENO);
	int command_exists;
	char *temp_buf;
	char *command;

	while (666)
	{
		write(1, "$ ", 2);
		readNO = getline(&userInput_buf, &size_buf, stdin);
		if (readNO == -1)
		{
			if (!is_interactive)
				break;
			perror("getline()");
			exit(EXIT_FAILURE);
		}
		if (userInput_buf[readNO - 1] == '\n')
			userInput_buf[readNO - 1] = '\0';
		if (userInput_buf[0] == '\0')
			continue;

		command_exists = 0;
		temp_buf = strdup(userInput_buf);
		command = strtok(temp_buf, " \t\n");
		if (command[0] == '/')
		{
			if (access(command, X_OK) == 0)
			{
				command_exists = 1;
			}
		}
		else
		{
			path = getenv("PATH");
			sprintf(path_search, "%s:/usr/bin", path);
			dir = strtok(path_search, ":");
			while (dir)
			{
				char command_path[4096];
				snprintf(command_path, sizeof(command_path), "%s/%s", dir, command);
				if (access(command_path, X_OK) == 0)
				{
					command_exists = 1;
					break;
				}
				dir = strtok(NULL, ":");
			}
		}

		free(temp_buf);

		if (!command_exists)
		{
			char error_message[100];
			sprintf(error_message, "%s: command not found", command);
			errno = ENOENT;
			perror(error_message);
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(userInput_buf);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			tok = strtok(userInput_buf, " \t\n\"");
			while (tok)
			{
				args = realloc(args, (i + 1) * sizeof(char *));
				args[i - 1] = malloc(sizeof(char) * strlen(tok) + 1);
				strcpy(args[i - 1], tok);
				i++;
				tok = strtok(NULL, " \t\n\"");
			}
			args[i - 1] = NULL;
			free(tok);

			if (args[0][0] == '/')
			{
				if (execve(args[0], args, NULL) == -1)
				{
					perror(userInput_buf);
					free(userInput_buf);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				char *path = getenv("PATH");
				if (path == NULL)
				{
					write(2, "PATH variable not found.\n", 25);
					exit(EXIT_FAILURE);
				}

				sprintf(path_search, "%s:/usr/bin", path);

				dir = strtok(path_search, ":");
				while (dir)
				{
					char command_path[4096];
					snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);
					if (access(command_path, X_OK) == 0)
					{
						if (execve(command_path, args, NULL) == -1)
						{
							perror(userInput_buf);
							free(userInput_buf);
							exit(EXIT_FAILURE);
						}
					}
					dir = strtok(NULL, ":");
				}
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
		if (!is_interactive)
			break;
	}
	free(userInput_buf);
	return (0);
}