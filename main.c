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

	while (666)
	{
		write(1, "$ ", 2);
		readNO = getline(&userInput_buf, &size_buf, stdin);
		if (readNO == -1)
		{
			perror("getline()");
			exit(EXIT_FAILURE);
		}

		if (userInput_buf[readNO - 1] == '\n')
			userInput_buf[readNO - 1] = '\0';
		if (userInput_buf[0] == '\0')
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(userInput_buf);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			tok = strtok(userInput_buf, " \t\n");
			while (tok)
			{
				args = realloc(args, (i + 1) * sizeof(char *));
				args[i - 1] = malloc(sizeof(char) * strlen(tok) + 1);
				strcpy(args[i - 1], tok);
				i++;
				tok = strtok(NULL, " \t\n");
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
					char *command_path = malloc(strlen(dir) + strlen(args[0]) + 2);
					strcpy(command_path, dir);
					strcat(command_path, "/");
					strcat(command_path, args[0]);

					if (access(command_path, X_OK) == 0)
					{
						if (execve(command_path, args, NULL) == -1)
						{
							perror(userInput_buf);
							free(userInput_buf);
							free(command_path);
							exit(EXIT_FAILURE);
						}
					}

					free(command_path);
					dir = strtok(NULL, ":");
				}

				write(2, args[0], strlen(args[0]));
				write(2, ": command not found\n", 20);
				free(userInput_buf);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
	}
	free(userInput_buf);
	return (0);
}
