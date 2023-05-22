#include "main.h"

/**
 * main - our main shell function
 * Return: 0 on success
 */

int main(void)
{
	char *userInput_buf = NULL;
	pid_t pid;
	size_t buf_size = 0;
	ssize_t readNO;
	char **args = NULL;
	int status;
	int is_interactive = isatty(STDIN_FILENO);

	while (666)
	{
		write(STDOUT_FILENO, "$ ", 2);
		readNO = getline(&userInput_buf, &buf_size, stdin);
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
		args = tokenize_input(userInput_buf);

		if (check_spaces_tabs(userInput_buf))
		{
			continue;
		}

		if (handle_builtins(args))
		{
			free(args);
			continue;
		}
		if (!command_exists(args))
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			free(args);
			continue;
		}
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
			}
			exit(EXIT_FAILURE);
		}
		if (wait(&status) == -1)
			perror("wait");
		free(args);
		if (!is_interactive)
			break;
	}
	free(userInput_buf);
	return (0);
}
