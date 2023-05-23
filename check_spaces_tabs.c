#include "main.h"
/**
 * check_spaces_tabs - checks if a string is only spaces and tabs
 * @str: user input buffer
 *
 * Return: 0 or 1
*/
int check_spaces_tabs(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}
