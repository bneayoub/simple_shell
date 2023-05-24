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

	signal(SIGINT, handle_sig);
	while (666)
	{
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
			free_args(args);
		}
		free(userInput_buf);
	}
	return (0);
}
