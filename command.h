#ifndef COMMAND_H
#define COMMAND_H 1

#include <string.h>

/* command argument delimiters */
#define COMMAND_ARGUMENT_DELIMITERS     " "

/* shell command structure */
typedef struct ShellCommand {
    char command[128];      /* the actual command */
    char *arguments[64];    /* array of pointers to above command */
    int n;                  /* number of shell command args */
} ShellCommand;

/* parser for shell command arguments */
int argument_parser(ShellCommand *sh_command);

#endif /* COMMAND_H */
