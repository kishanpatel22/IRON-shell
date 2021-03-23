#include "builtin.h"
#include "global.h"

/* check if the command is shell buildin command example
 * 1) cd
 * 2) history 
 * 3) exit
 * 4) fg
 * 5) bg
 * 6) jobs
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
    } else if(strcmp(command, FG_COMMAND) == 0) {
        return true;
    } else if(strcmp(command, BG_COMAMND) == 0) {
        return true;
    } else if(strcmp(command, JOBS_COMMAND) == 0) {
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
    } else if(strcmp(command, FG_COMMAND) == 0) {
        return FG;
    } else if(strcmp(command, BG_COMAMND) == 0) {
        return BG;
    } else if(strcmp(command, JOBS_COMMAND) == 0) {
        return JOBS;
    }
    /* its no a shell command */ 
    return -1;
}

/* executes the shell buildin comamnd */
void execute_shell_builtin_command(char *command) {
    
    char cwd[512];
    IronShellCommand shell_command;
    strcpy(shell_command.command, command);
    command_argument_parser(&shell_command);

    int command_type = builtin_shell_command_number(shell_command.arguments[0]);

    /* set the appropriate signal handlers */
    set_signals();

    /* initialize the foreground job */
    init_job(&(iscb.fg_job), "");

    switch(command_type) {

        /* change the directory */
        case CHANGE_DIR:
            /* store the current working directory */
            getcwd(cwd, 512);
            /* more than two arguments to cd is not permissible */
            if(shell_command.n > 2) {
                PRINT_EXECPTION("cd : too many arguments !");
                return;
            } else if(shell_command.arguments[1] == NULL) {
                chdir(HOME_DIR);
                strcpy(iscb.pwd, cwd);
            } else if(strcmp(shell_command.arguments[1], "-") == 0) {
                chdir(iscb.pwd);
                strcpy(iscb.pwd, cwd);
            } else if(chdir(shell_command.arguments[1]) == -1) {
                PRINT_EXECPTION("cd : No such file or directory !\n");
                return;
            }
            break;

        /* HISTORY operation in the shell */
        case HISTORY:
            break;

        /* BG command to run process in background */
        case BG:
            if(shell_command.n > 2) {
                PRINT_EXECPTION("bg works with only index numbers of jobs");
                break;
            } else if(shell_command.n == 2) {
                resume_job_bg(&(iscb.jobs), atoi(shell_command.arguments[1]));
                return;
            } else {
                resume_job_bg(&(iscb.jobs), 1);
                return;
            }
            break;
            
        /* FG command to run process in foreground */
        case FG:
            if(shell_command.n > 2) {
                PRINT_EXECPTION("fg works with only index numbers of jobs");
                break;
            } else if(shell_command.n == 2) {
                resume_job_fg(&(iscb.jobs), atoi(shell_command.arguments[1]), &(iscb.fg_job));
            } else {
                resume_job_fg(&(iscb.jobs), 1, &(iscb.fg_job));
            }
            
            /* wait for all the concurrently running process to get over */
            for(int i = 0; i < iscb.fg_job.process_count; i++) {
                /* wait pid waits for any process to changes its state */
                waitpid(-1, NULL, WUNTRACED);
            }
            
            /* destroy the job */
            destroy_job(&(iscb.fg_job));

            break;
        
        /* JOBS command to display list of suspended and running processes */
        case JOBS:
            print_jobs(iscb.jobs);
            break;

        /* exit command */
        case EXIT:
            destroy_jobs(&(iscb.jobs));
            /* terminate the program */
            exit(errno);

        /* invalid command as input */
        default:
            break;
    }
        
    /* reset the original signals handlers */
    reset_signals();
}


