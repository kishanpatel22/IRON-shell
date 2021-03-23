#ifndef IRON_SHELL_H
#define IRON_SHELL_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "command_handler.h"
#include "signals.h"
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
    
    int count_jobs;                     /* number of such jobs */

} IronShellJobList;


/* IRON-shell Control Block                                                 */
typedef struct IronShellControlBlock {
    
    IronShellJob fg_job;                /* currently executing foreground job */
    
    double execution_time;              /* execution time of last command */
    
    char history_commands_file[128];    /* command history log file */
    
    IronShellJobList jobs;              /* list of currently suspened and runing jobs */
    
    char pwd[128];                      /* previous working directory */

} IronShellControlBlock;


/* initializes the shell control block */
void init_shell_control_block(IronShellControlBlock *iscb);

/* initializes the job list data structure for suspended or runnning tasks  */
void init_job_list(IronShellJobList *jobs);

/* add job to the job list */
void add_job(IronShellJobList *jobs, IronShellJob job);

/* resumes job in foreground */
void resume_job_fg(IronShellJobList *jobs, int index, IronShellJob *job);

/* resumes job in background */
void resume_job_bg(IronShellJobList *jobs, int index);

/* prints the current running and suspended jobs */
void print_jobs(IronShellJobList jobs);

/* destory all the jobs which are currently active */
void destroy_jobs(IronShellJobList *jobs);

/* returns true if there no jobs present in background */
bool no_jobs(IronShellJobList jobs);

/* delelte the job having the given pid */
bool delete_job(IronShellJobList *jobs, pid_t pid);


#endif /* IRON_SHELL_H */


