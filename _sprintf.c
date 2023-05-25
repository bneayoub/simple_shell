#include "main.h"

/**
 * _sprintf - Our version of sprintf
 * @str: The string to be concatenated
 * @delim: The delimiter to be concatenated
 * @src: The source string
 * Return: Pointer to the new string
 */

char *_sprintf(char *str, char *delim, char *src)
{
	char *new_str;
	int len_str, len_delim, len_src;

	len_str = _strlen(str);
	len_delim = _strlen(delim);
	len_src = _strlen(src);

	new_str = malloc((len_str + len_delim + len_src + 1) * sizeof(char));
	if (new_str == NULL)
	{
		perror("Error: malloc failed in _sprintf");
		exit(EXIT_FAILURE);
	}

	_strcpy(new_str, str);
	_strcat(new_str, delim);
	_strcat(new_str, src);

	return (new_str);
}
