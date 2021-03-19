#ifndef IRON_SHELL_H
#define IRON_SHELL_H 1

#include <stdio.h>
#include <stdlib.h>

#define HISTORY_LOG         "/tmp/iron-shell-logs.txt"

/* status of the last command executed on the interface                     */
enum iron_command_status {NO_COMMAND, EXECUTION, SUSPENDED, RESUMED, TERMINATED};

/* IRON-shell Control Block                                                 */
typedef struct IronShellControlBlock {
    
    CommandProcess *command_process;                /* currently executing process */
    
    double execution_time;                          /* execution time of last command */
    
    int command_execution_status;                   /* execution status of last command */
    
    char history_commands_file[128];                /* command history log file */
    
    IronShellSuspendedCommands suspended_commands;  /* queue of command */
    
} IronShellControlBlock;


/* initializes the shell control block */
void init_shell_control_block(IronShellControlBlock *scb) {
    
    /* current status of command */
    scb->command_execution_status = NO_COMMAND;
    
    /* history log file                         */
    strcpy(scb->history_commands_file, HISTORY_LOG);
    
    /* suspended list of commands for the shell */
    scb->suspended_commands = NULL;
    
    /* execution time of the last command */
    scb->execution_time = 0.0;

}

#endif /* IRON_SHELL_H */
