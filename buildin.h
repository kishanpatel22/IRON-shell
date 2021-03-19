#ifndef BUILDIN_H
#define BUILDIN_H 1

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "command.h"

/* Module provides basic functionalities that are provided by shell 
 * which include changing directories, history executed and exiting the
 * shell
 */

/* print the error message on the terminal */
#define buildin_error(msg, ...)                                     \
    fprintf(stderr,"shell error : " msg)                            \

#define CD_COMMAND          "cd"
#define HISTORY_COMMAND     "history"
#define EXIT_COMMAND        "exit"

/* uniques values for identification for the buildin shell commands */
#define CHANGE_DIR      (1)
#define HISTORY         (2)
#define EXIT            (3)

/* checks the command is shell build in command */
bool check_buildin_command(char *command_buffer);

/* returns the unique number of the shell command */
int buildin_shell_command_number(char *command);

/* executes the shell buildin command */
void execute_shell_buildin_command(char *command);

#endif /* BUILDIN_H */

