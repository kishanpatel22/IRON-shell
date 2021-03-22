#include "iron_shell.h"
#include "global.h"

/* initializes the iron shell control block */
void init_shell_control_block(IronShellControlBlock *iscb) {
    
    /* initialize the foreground command running in shell */
    init_job(&(iscb->fg_job), "");

    /* execution time of the last command */
    iscb->execution_time = 0.0;
    
    /* history log file                         */
    strcpy(iscb->history_commands_file, HISTORY_LOG);
    
    /* suspended or running list of jobs for the shell */
    init_job_list(&(iscb->jobs));
}

/* initializes the job list data structure for suspended or runnning tasks  */
void init_job_list(IronShellJobList *jobs) {
    jobs->head = jobs->tail = NULL;
    jobs->count_jobs = 0;
    return;
}

/* add job to the job list */
void add_job(IronShellJobList *jobs, IronShellJob job) {
    IronShellJobNode *new_job_node = (IronShellJobNode *)malloc(sizeof(IronShellJobNode));
    if(new_job_node == NULL) {
        eprintf("malloc failed\n"); 
    }
    new_job_node->job = job;
    new_job_node->next = NULL;
    
    /* first job to be added in the job list */
    if(jobs->head == NULL && jobs->tail == NULL) {
        jobs->head = jobs->tail = new_job_node;
        jobs->count_jobs++;
        return;
    }
    new_job_node->next = jobs->head;
    jobs->head = new_job_node;
    jobs->count_jobs++;
    return;
}


/* resumes job in foreground */
void resume_job_fg(IronShellJobList *jobs, int index, IronShellJob *job) {
    if(no_jobs(*jobs)) {
        printf("iron-shell : no foreground jobs present\n"); 
        return;
    } 
    IronShellJobNode* ptr = jobs->head, *temp = NULL;
    while(ptr != NULL && index > 1) {
        temp = ptr;
        ptr = ptr->next;
        index--;
    }
    if(ptr == NULL) {
        printf("iron-shell : no foreground jobs for given argument \n");
        return;
    }
    /* job which is suspended is made to start again in foreground 
     * note is process is already running in background then just wait
     */
    if(ptr->job.command_status == STOPPED) {
        resume_job(&(ptr->job), index);
    }
    *job = ptr->job;

    /* delete the node from the job list */
    if(temp == NULL) {
        /* deleting the first node in the list */
        jobs->head = jobs->head->next;
        free(ptr);
    } else {
        temp->next = ptr->next;
        free(ptr);
    }
    jobs->count_jobs--;
    return;
}


/* resumes job in background */
void resume_job_bg(IronShellJobList *jobs, int index) {
    if(no_jobs(*jobs)) {
        printf("iron-shell : no background jobs present\n");
        return;
    }
    IronShellJobNode* ptr = jobs->head;
    while(ptr != NULL && index > 1) {
        ptr = ptr->next;
        index--;
    }
    if(ptr == NULL) {
        printf("iron-shell : no background jobs for given argument \n");
        return;
    }
    /* there is not change in the data structure */
    if(ptr->job.command_status == RUNNING) {
        printf("iron-shell : the process is already running in background\n");
        return;
    } else {
        resume_job(&(ptr->job), index);
    }
    return;
}


/* traverse the job lists : prints the list of running and suspensed jobs */
void print_jobs(IronShellJobList jobs) {
    IronShellJobNode *ptr = jobs.head;
    if(ptr == NULL) {
        printf("iron-shell : no suspeneded or stopped jobs\n");
        return;
    }
    int i = 1;
    while(ptr != NULL) {
        print_job(ptr->job, i++);
        ptr = ptr->next;
    }
}


/* destory all the jobs which are currently active */
void destroy_jobs(IronShellJobList *jobs) {
    IronShellJobNode *ptr = jobs->head, *temp;
    while(ptr != NULL) {
        kill_job(&(ptr->job));
        jobs->count_jobs--;
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
    jobs->head = jobs->tail = NULL;
    return;
}


/* returns true if there are no jobs suspended or running */
bool no_jobs(IronShellJobList jobs) {
    if(jobs.head == NULL && jobs.tail == NULL) {
        return true;
    }
    return false;
}

/* delelte the job having the given pid */
bool delete_job(IronShellJobList *jobs, pid_t pid) {
    IronShellJobNode *ptr = jobs->head, *temp = NULL;
    int index = 1;
    while(ptr != NULL) {
        if(delete_sub_job(&(ptr->job), pid, index)) {
            /* now check if the given process is completely done
             * thus free the allocated memory to data structure 
             */
            if(ptr->job.head == NULL) {
                if(temp == NULL) {
                    jobs->head = ptr->next;
                    if(jobs->head == NULL) {
                        jobs->tail = NULL;
                    }
                } else {
                    temp->next = ptr->next; 
                }
                free(ptr);
            } 
        }  
        temp = ptr;
        ptr = ptr->next;
        index++;
    }
    return false;
}
