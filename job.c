#include "job.h"

/* initializes the job list data structure */
void init_job(IronShellJob *job) {
    job->head = job->tail = NULL;
    job->process_count = 0;
    return;
}

/* adds sub job to the exisition job list data structure */
void add_sub_job(IronShellJob *job, char *command_name, pid_t pid) {
    IronShellJobProcess *new_sub_job = 
        (IronShellJobProcess *)malloc(sizeof(IronShellJobProcess));
    if(new_sub_job == NULL) {
        eprintf("malloc failed\n"); 
        exit(1);
    }
    strcpy(new_sub_job->command_name, command_name);
    new_sub_job->pid = pid;
    new_sub_job->next = NULL;
    
    /* first job to the added in the list */
    if(job->head == NULL && job->tail == NULL) {
        job->head = job->tail = new_sub_job; 
        return;
    }
    job->tail->next = new_sub_job;
    job->tail = new_sub_job;
    return;
}

/* void traverse the job list */
void traverse_job(IronShellJob job) {
    IronShellJobProcess *ptr = job.head;
    while(ptr != NULL) {
        printf("(%s, %d)\t", ptr->command_name, ptr->pid);
        ptr = ptr->next;
    }
    printf("\n");
    return;
}

/* destories the job and allocated resources */
void destroy_job(IronShellJob job) {
    IronShellJobProcess *ptr = job.head, *temp;
    while(ptr != NULL) {
        temp = ptr->next; 
        free(ptr);
        ptr = temp;
    }
    return;
}



