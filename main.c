#include "main.h"

/**
 * main - our main shell function
 * Return: 0 on success
 */
int main(void)
{
	char *userInput_buf, **args = NULL;
	size_t buf_size = 0;
	ssize_t readNO, i;

	while (666)
	{
		userInput_buf = NULL;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		readNO = read_user_input(&userInput_buf, &buf_size);
		if (readNO == -1)
		{
			free(userInput_buf);
			break;
		}
		if (userInput_buf[0] == '\0')
		{
			free(userInput_buf);
			continue;
		}
		if (check_spaces_tabs(userInput_buf))
		{
			free(userInput_buf);
			continue;
		}
		args = tokenize_input(userInput_buf);
		if (!validate_command(args, userInput_buf))
		{
			free(userInput_buf);
			continue;
		}
		execute_forked_command(args, userInput_buf);
		if (args != NULL)
		{
			for (i = 0; args[i] != NULL; i++)
				free(args[i]);
			free(args);
		}
		free(userInput_buf);
	}
	return (0);
}
