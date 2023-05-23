#include "main.h"

/**
 * main - our main shell function
 * Return: 0 on success
 */

int main(void)
{
	char *userInput_buf = NULL;
	size_t buf_size = 0;
	ssize_t readNO;
	char **args = NULL;

	while (666)
	{
		write(STDOUT_FILENO, "$ ", 2);
		readNO = read_user_input(&userInput_buf, &buf_size);
		if (readNO == -1)
			break;
		if (userInput_buf[0] == '\0')
			continue;
		args = tokenize_input(userInput_buf);
		if (check_spaces_tabs(userInput_buf))
		{
			continue;
		}
		if (!validate_command(args))
		{
			continue;
		}
		execute_forked_command(args, userInput_buf);
		free(args);
		if (!isatty(STDIN_FILENO))
			break;
	}
	free(userInput_buf);
	return (0);
}
