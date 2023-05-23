#include "main.h"
/**
 * tokenize_input - tokenize our input
 * @userInput_buf: user input buffer to tokenize
 *
 * Return: array of tokenized strings
 */
char **tokenize_input(char *userInput_buf)
{
    char **args = NULL;
    char *separator = " \n\t";
    char *parsed;
    int index = 0;

    parsed = strtok(userInput_buf, separator);

    while (parsed != NULL)
    {
        args = realloc(args, (index + 2) * sizeof(char *));
        args[index] = malloc(strlen(parsed) + 1);
        strcpy(args[index++], parsed);
        parsed = strtok(NULL, separator);
    }

    args[index] = NULL;
    return args;
}
