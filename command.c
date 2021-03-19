#include "command.h"

/* parses the arguments of given shell command */
int argument_parser(ShellCommand *sh_command) {
    sh_command->n = 0;
    char *args = strtok(sh_command->command, COMMAND_ARGUMENT_DELIMITERS);
    while(args != NULL) {
        sh_command->arguments[sh_command->n] = args;
        sh_command->n++;
        args = strtok(NULL, COMMAND_ARGUMENT_DELIMITERS);
    }
    sh_command->arguments[sh_command->n] = NULL;
    return 0;
}

