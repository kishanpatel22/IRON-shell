#ifndef COMMAND_PROCESS_LIST_H
#define COMMAND_PROCESS_LIST_H 1

#include "command.h"

#define MAX_COMMAND_PROCESS_SIZE    (128)

/* the module provides the process command queue data structure implementation 
 * Each command which is executed is basically a process and when multiple 
 * commands are executed by the shell concurrently the 
 */

/* IRON-shell process command structure */
typedef struct ProcessCommandNode {
    
    char process_command[MAX_COMMAND_PROCESS_SIZE];   /* name of the process */
    
    pid_t pid;                                        /* pid of the process */

    struct ProcessCommandNode *next;                  /* next element in the list */

} ProcessCommandNode;

/* IRON-shell the process command list  */
typedef struct ProcessCommandList {
    
    ProcessCommandNode *head, *tail;            /* head and tail of queue */

    int process_commands_count;                 /* number of process commands */

} ProcessCommandList;

/* initializes the process command list */
void init_process_command_list(ProcessCommandList *pcl);

/* enqueue process command inside the process command list  */
void enqueue_process_command(ProcessCommandList *pcl, char *command_name, pid_t pid);

/* void traverse the process command list */
void traverse_process_command_list(ProcessCommandList pcl);

/* destories the process command list */
void destroy_process_command_list(ProcessCommandList pcl);

#endif /* COMMAND_PROCESS_LIST_H */


