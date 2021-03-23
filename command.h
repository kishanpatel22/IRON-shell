#ifndef COMMAND_H
#define COMMAND_H 1

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "log.h"

/* command argument delimiters                                              */
#define COMMAND_ARGUMENT_DELIMITERS     " "

#define MAX_COMMAND_SIZE                (1024)
#define MAX_ARGS                        (16)

/* IRON-shell command structure                                             */
typedef struct IronShellCommand {
    char command[MAX_COMMAND_SIZE];     /* command string                   */
    char *arguments[MAX_ARGS];          /* array of pointers to the command */
    int n;                              /* number of iron-shell command args*/
} IronShellCommand;

int command_argument_parser(IronShellCommand *sh_command);



#endif /* COMMAND_H */
