#ifndef BUILDIN_H
#define BUILDIN_H 1

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "command.h"

/* Module provides basic functionalities that are provided by iron-shell 
 * which include changing directories, history executed and exiting iron-shell
 */

/* logs for iron-shell error message                                        */
#define builtin_error(msg, ...)                                     \
    fprintf(stderr,"IRON-shell error : " msg)                       \


#define CD_COMMAND              "cd"
#define HISTORY_COMMAND         "history"
#define EXIT_COMMAND            "exit"
#define FG_COMMAND              "fg"
#define BG_COMAMND              "bg"


/* identifier values for identification for the builtin shell commands      */
#define CHANGE_DIR              (1)
#define HISTORY                 (2)
#define EXIT                    (3)


/* maximum length of the directory                                          */
#define MAX_DIR_LENGHT          (512)


/* checks the command is iron-shell built in command                        */
bool check_builtin_command(char *command_buffer);

/* returns the unique identifier of iron-shell command                      */
int builtin_shell_command_number(char *command);

/* executes the iron-shell builtin command                                  */
void execute_shell_builtin_command(char *command);

#endif /* BUILDIN_H */
