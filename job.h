#ifndef JOB_H
#define JOB_H 1

#include <signal.h>
#include <stdbool.h>
#include "command.h"

#define MAX_PROCESS_NAME_SIZE           (128)

/* status of the last command executed on the interface                     */
enum shell_command_status {NO_COMMAND, RUNNING, STOPPED};


/* The module provides implementation details related to the IRON-shell JOB
 * JOB is defined as single unit of work done by shell, i.e. it is single
 * process of group of process which are created by shell using single user command
 */

/* IRON-shell JOB process structure */
typedef struct IronShellJobProcess {
    
    char process_name[MAX_PROCESS_NAME_SIZE];       /* name of process */

    pid_t pid;                                      /* pid of process associated with command */

    struct IronShellJobProcess *next;               /* next element in the list */

} IronShellJobProcess;


/* IRON-shell JOB structure which is implemented using List data structure  */
typedef struct IronShellJob {
    
    IronShellJobProcess *head, *tail;   /* head and tail of queue */
    
    char command[MAX_COMMAND_SIZE];     /* the actual command name */

    int command_status;                 /* status of the command */

    int process_count;                  /* number of process created by single command */

} IronShellJob;


/* initializes the job list data structure */
void init_job(IronShellJob *job, char *command);

/* adds sub job to the exisition job list data structure */
void add_sub_job(IronShellJob *job, char *command_name, pid_t pid);

/* void traverse the job list */
void traverse_job(IronShellJob job);

/* destories the job and allocated resources */
void destroy_job(IronShellJob *job);

/* kills the job's running processes and free the allocated resources */
void kill_job(IronShellJob *job);

/* suspends the job's running processes */
void suspend_job(IronShellJob *job);

/* resumes the execution of the job */
void resume_job(IronShellJob *job, int index);

/* logs the message of the job on the console  */
void print_job(IronShellJob job, int index);

/* deletes a sub job process with given pid */
bool delete_sub_job(IronShellJob *jobs, pid_t pid, int index);

#endif /* JOB_H */

