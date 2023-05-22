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
	char i = 1;

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
			if (execve(args[0], args, NULL) == -1)
			{
				perror(userInput_buf);
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