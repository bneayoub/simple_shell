#include "main.h"

/**
 * handle_sig - handle signal
 * @sig: signal
 * Return: void.
 */
void handle_sig(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 4);
	fflush(stdout);
}
