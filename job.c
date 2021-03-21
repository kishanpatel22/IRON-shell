#include "job.h"
#include "global.h"

/* initializes the job list data structure */
void init_job(IronShellJob *job, char *command) {
    job->head = job->tail = NULL;
    strcpy(job->command, command);
    job->process_count = 0;
    job->command_status = RUNNING;
    return;
}

/* adds sub job to the exisition job list data structure */
void add_sub_job(IronShellJob *job, char *command_name, pid_t pid) {
    IronShellJobProcess *new_sub_job = 
        (IronShellJobProcess *)malloc(sizeof(IronShellJobProcess));
    if(new_sub_job == NULL) {
        eprintf("malloc failed\n"); 
    }
    strcpy(new_sub_job->process_name, command_name);
    new_sub_job->pid = pid;
    new_sub_job->next = NULL;
    
    /* first job to the added in the list */
    if(job->head == NULL && job->tail == NULL) {
        job->head = job->tail = new_sub_job; 
        job->process_count++;
        return;
    }
    new_sub_job->next = job->head;
    job->head = new_sub_job;
    job->process_count++;
    return;
}

/* void traverse the job list */
void traverse_job(IronShellJob job) {
    IronShellJobProcess *ptr = job.head;
    while(ptr != NULL) {
        printf("(%s, %d)\t", ptr->process_name, ptr->pid);
        ptr = ptr->next;
    }
    printf("\n");
    return;
}

/* destories the job and allocated resources */
void destroy_job(IronShellJob* job) {
    IronShellJobProcess *ptr = job->head, *temp;
    while(ptr != NULL) {
        temp = ptr->next; 
        free(ptr);
        ptr = temp;
    }
    job->head = job->tail = NULL;
    job->process_count = 0;
    return;
}

/* kills the job's running process 
 * Note : this frees the dynamically allocated resources 
 */
void kill_job(IronShellJob *job) {
    IronShellJobProcess *ptr = job->head;
    while(ptr != NULL) {
        kill(ptr->pid, SIGINT); 
        ptr = ptr->next;
    }
    destroy_job(job);
    return;
}

/* suspends the job's running processes 
 * Note this doesn't free the dynamically allocated resources 
 */
void suspend_job(IronShellJob *job) {
    IronShellJobProcess *ptr = job->head;
    job->command_status = SUSPENDED;
    while(ptr != NULL) {
        kill(ptr->pid, SIGSTOP);
        ptr = ptr->next;
    }
    print_job(*job, iscb.jobs.count_jobs + 1);
    return;
}

/* resumes the execution of the job and since any paritcular 
 * job contains many process thus execution all process is resumed.
 */
void resume_job(IronShellJob *job, int index) {
    IronShellJobProcess *ptr = job->head;
    if(ptr == NULL) {
        printf("iron-shell : no process assicated with the job\n");
        return;
    } 
    while(ptr != NULL) {
        kill(ptr->pid, SIGCONT);
        ptr = ptr->next; 
    }
    job->command_status = RUNNING;
    print_job(*job, index);
    return;
}


void print_job(IronShellJob job, int index) {
    IronShellJobProcess *ptr = job.head;
    if(ptr == NULL) {
        eprintf("suspended job without any processes\n");
    }
    if(job.command_status == SUSPENDED) {
        printf("\n [%d]\t+ %d suspended\t%s\n", index, ptr->pid, ptr->process_name);
    } else {
        printf("\n [%d]\t- %d running  \t%s\n", index, ptr->pid, ptr->process_name);
    }
    ptr = ptr->next;
    while(ptr != NULL) {
        if(job.command_status == SUSPENDED) {
            printf("     \t+ %d suspended\t%s\n", ptr->pid, ptr->process_name);
        } else {
            printf("     \t- %d running  \t%s\n", ptr->pid, ptr->process_name);
        }
        ptr = ptr->next;
    }
    return;
}



