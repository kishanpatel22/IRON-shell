#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H 1

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "command.h"

/* print the error message on the terminal */
#define eprintf(msg, ...)                                           \
    fprintf(stderr,"shell error : " msg                             \
            "\nfile = %s, line number = %d, in function = %s()\n"   \
            ##__VA_ARGS__, __FILE__, __LINE__, __func__);           \
    exit(errno);                                                    \


/* max length of the command that user can enter */
#define MAX_COMMAND_LENGHT              (1024)

/* FINITE STATE MACHINE STATES for parsing the shell command */
#define START                           (100)
#define COMMAND                         (200)
#define PIPE                            (300)
#define INPUT_REDIRECT                  (400)
#define OUTPUT_REDIRECT                 (500)
#define NON_BLOCKING_COMMAND            (600)
#define END                             (700)

#define INVALID                         (-1)

/* reads the mulitple shell command from user */
int read_command(char *command_buffer, int max_command_length);

/* returns the shell delimiter state */
int get_shell_delimiter_state(char shell_delimiter);

/* checks if the given character is shell delimiter */
bool check_shell_delimiter(char ch);

/* parser for the multiple shell commads */
int parser(char *token, char *command);

/* FSM based approach for command handler */
void command_handler(char *command_buffer);

/* function executes the shell commands by blocking the shell prompt */
void execute_blocking_shell_command(ShellCommand shell_command);

/* function executes the shell commands concurrently without blocking 
 * the shell prompt with the sense of background process 
 */
void execute_non_blocking_shell_command(ShellCommand shell_command);

/* function executes the shell command connecting to a pipe */
void execute_shell_command_with_pipe(ShellCommand shell_command, int pfd[]);

#endif /* COMMAND_HANDLER_H */

