#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

extern char **environ;

int command_exists(char **args);
int execute_command(char **args, char *userInput_buf);
int handle_builtins(char **args);
char **tokenize_input(char *userInput_buf);
int check_spaces_tabs(char *str);
ssize_t read_user_input(char **userInput_buf, size_t *buf_size);
void execute_forked_command(char **args, char *userInput_buf);
int validate_command(char **args);

#endif /* MAIN_H */
