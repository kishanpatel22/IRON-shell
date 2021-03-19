#include "builtin.h"


/* check if the command is shell buildin command example
 * 1) cd
 * 2) history 
 * 3) exit
 * 4) fg
 * 5) bg
 * On success returns the true, else false
 */

bool check_builtin_command(char *command_buffer) {
    char command[128];
    int index = 0;
    while(command_buffer[index] != ' ' && command_buffer[index] != '\0') {
        command[index] = command_buffer[index];
        index++;
    }
    command[index] = '\0';

    /* compare with the build in shell commands */
    if(strcmp(command, CD_COMMAND) == 0) {
        return true;
    } else if(strcmp(command, HISTORY_COMMAND) == 0) {
        return true;
    } else if(strcmp(command, EXIT_COMMAND) == 0) {
        return true;
    } 
    /* its no a shell command */ 
    return false;
}

/* returns the unique number of the shell command */
int builtin_shell_command_number(char *command) {
    if(strcmp(command, CD_COMMAND) == 0) {
        return CHANGE_DIR;
    } else if(strcmp(command, HISTORY_COMMAND) == 0) {
        return HISTORY;
    } else if(strcmp(command, EXIT_COMMAND) == 0) {
        return EXIT;
    } 
    /* its no a shell command */ 
    return -1;
}

/* executes the shell buildin comamnd */
void execute_shell_builtin_command(char *command) {
    
    IronShellCommand shell_command;
    strcpy(shell_command.command, command);
    command_argument_parser(&shell_command);

    int command_type = builtin_shell_command_number(shell_command.arguments[0]);

    switch(command_type) {

        /* change the directory */
        case CHANGE_DIR:
            /* more than two arguments to cd is not permissible */
            if(shell_command.arguments[2] != NULL) {
                builtin_error("cd : too many arguments !\n");
            } else if(chdir(shell_command.arguments[1]) == -1) {
                builtin_error("cd : No such file or directory !\n");
            }
            break;

        /* HISTORY operation in the shell */
        case HISTORY:
            break;

        /* exit command */
        case EXIT:
            /* terminate the program */
            exit(errno);

        /* invalid command as input */
        default:
            break;
    }
}


