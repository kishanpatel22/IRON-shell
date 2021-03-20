#include "command.h"

/* parses the arguments of given iron shell command                         */
int command_argument_parser(IronShellCommand *sh_command) {

    /* initialize the number of arguments of the command                    */
    sh_command->n = 0;

    /* loop through the shell comamnd for parsing arguments                 */
    char *args = strtok(sh_command->command, COMMAND_ARGUMENT_DELIMITERS);
    while(args != NULL) {
        sh_command->arguments[sh_command->n] = args;
        sh_command->n++;
        args = strtok(NULL, COMMAND_ARGUMENT_DELIMITERS);
    }

    /* last argument is NULL (helps in exec)                                */
    sh_command->arguments[sh_command->n] = NULL;

    return 0;
}

