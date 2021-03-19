#include "process_command_list.h"

/* initializes the process command list */
void init_process_command_list(ProcessCommandList *pcl) {
    pcl->head = pcl->tail = NULL;
    pcl->process_commands_count = 0;
}

/* enqueue process command inside the process command list  */
void enqueue_process_command(ProcessCommandList *pcl, char *command_name, pid_t pid) {
    ProcessCommandNode *new_process_command =  (ProcessCommandNode *)malloc(sizeof(ProcessCommandNode));
    if(new_process_command == NULL) {
        eprintf("memory allocation failed");
    }
    strcpy(new_process_command->process_command, command_name);
    new_process_command->pid = pid;
    new_process_command->next = NULL;
    
    /* first new node in the queue */
    if(pcl->head == NULL && pcl->tail == NULL) {
        pcl->head = pcl->tail = new_process_command;
        return;
    }
    /* append the new node at the last */
    pcl->tail->next = new_process_command;
    pcl->tail = new_process_command;
    return;
}

/* void traverse the process command list */
void traverse_process_command_list(ProcessCommandList pcl) {
    ProcessCommandNode *ptr = pcl.head;
    while(ptr != NULL) {
        printf("(%s, %d)\t", ptr->process_command, ptr->pid);
        ptr = ptr->next;
    }
    printf("\n");
    return;
}

/* destories the process command list */
void destroy_process_command_list(ProcessCommandList pcl) {
    ProcessCommandNode *ptr, *temp;
    ptr = pcl.head;
    while(ptr != NULL) {
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
}



