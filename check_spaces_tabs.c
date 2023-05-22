#include "main.h"

int check_spaces_tabs(char *str)
{
	while(*str)
	{
		if (*str != ' ' && *str !='\t')
			return (0);
		str++;
	}
	return (1);
}
