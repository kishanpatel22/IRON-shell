#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H 1

#include "command.h"

/* FINITE STATE MACHINE STATES for parsing the shell command */
#define START                           (100)
#define COMMAND                         (200)
#define PIPE                            (300)
#define INPUT_REDIRECT                  (400)
#define OUTPUT_REDIRECT                 (500)
#define NON_BLOCKING_COMMAND            (600)
#define END                             (700)

#define INVALID                         (-1)

/* parser for shell command arguments                                       */
int command_argument_parser(IronShellCommand *sh_command);

/* reads the mulitple shell command from user                               */
int read_command(char *command_buffer, int max_command_length);

/* returns the shell delimiter state                                        */
int get_shell_delimiter_state(char shell_delimiter);

/* checks if the given character is shell delimiter                         */
bool check_shell_delimiter(char ch);

/* parser for the multiple shell commads                                    */
int parser(char *token, char *command);

/* FSM based approach for command handler                                   */
void command_handler(char *command_buffer);

/* function executes the iron shell commands concurrently without blocking 
 * the shell prompt with the sense of background process 
 */
void execute_shell_command(IronShellCommand shell_command);

/* function executes the iron shell command connecting to a pipe            */
void execute_shell_command_with_pipe(IronShellCommand shell_command, int pfd[]);

#endif /* COMMAND_HANDLER_H */
