#ifndef IRON_SHELL_H
#define IRON_SHELL_H 1

#include <stdio.h>
#include <stdlib.h>

#include "command_handler.h"
#include "builtin.h"
#include "job.h"

#define HISTORY_LOG         "/tmp/iron-shell-logs.txt"

#define MAX_JOBS            (1024)


typedef struct IronShellJobNode {
    
    IronShellJob job;                   /* the job which is suspended */
    
    struct IronShellJobNode *next;      /* the next job reference in list */

} IronShellJobNode;


typedef struct IronShellJobList {
    
    IronShellJobNode *head, *tail;      /* list of jobs suspended or running */
    
    int num_jobs;                       /* number of such jobs */

} IronShellJobList;


/* IRON-shell Control Block                                                 */
typedef struct IronShellControlBlock {
    
    IronShellJob fg_job;                /* currently executing foreground job */
    
    double execution_time;              /* execution time of last command */
    
    char history_commands_file[128];    /* command history log file */
    
    IronShellJobList jobs;              /* list of currently suspened and runing jobs */
    
} IronShellControlBlock;


/* initializes the shell control block */
void init_shell_control_block(IronShellControlBlock *iscb);

/* initializes the job list data structure for suspended or runnning tasks  */
void init_job_list(IronShellJobList *jobs);


#endif /* IRON_SHELL_H */
