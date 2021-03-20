#include "iron_shell.h"

/* initializes the iron shell control block */
void init_shell_control_block(IronShellControlBlock *iscb) {
    
    /* initialize the foreground command running in shell */
    init_job(&(iscb->fg_job));

    /* execution time of the last command */
    iscb->execution_time = 0.0;
    
    /* history log file                         */
    strcpy(iscb->history_commands_file, HISTORY_LOG);
    
    /* suspended or running list of jobs for the shell */
    init_job_list(&(iscb->jobs));
}

/* initializes the job list data structure for suspended or runnning tasks  */
void init_job_list(IronShellJobList *jobs) {
    return;
}


