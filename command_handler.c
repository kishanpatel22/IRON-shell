#include "command_handler.h"

/* global variable keeps the track of where next token to be extracted */
static int parser_index;

/* shell delimiters are pipes, redirects and ampersand */
const char shell_delimiters[] = {'|', '>', '<', '&'};

/* reads the command from standard input */
int read_command(char *command_token, int max_command_length) {
    int i = 0, ch;
    while((ch = getchar()) != '\n' && ch != EOF && i < max_command_length) {
        command_token[i++] = ch;
    }
    command_token[i] = '\0';
    return i == 0 && ch == EOF ? -1 : i;
}

/* checks if the given character is shell delimiter */
bool check_shell_delimiter(char ch) {
    int n = sizeof(shell_delimiters) / sizeof(shell_delimiters[0]);
    for(int i = 0; i < n; i++) {
        if(shell_delimiters[i] == ch) {
            return true;
        }
    }
    return false;
}

/* returns the state of given shell delimiter */
int get_shell_delimiter_state(char shell_delimiter) {
    if(shell_delimiter == '|') {
        return PIPE;
    }
    if(shell_delimiter == '<') {
        return INPUT_REDIRECT;
    }
    if(shell_delimiter == '>') {
        return OUTPUT_REDIRECT;
    }
    if(shell_delimiter == '&') {
        return NON_BLOCKING_COMMAND;
    }
    return INVALID;
}

/* tokenizer : returns the next token */
int parser(char *token, char *command) {
    int n = strlen(command);
    /* skip the spaces */
    while(command[parser_index] == ' ' && parser_index < n) {  
        parser_index++; 
    }
    /* parse given commannd */
    /* CASE 1 : end of the command */
    if(parser_index == n)  {
        return END;   
    }

    /* CASE 2 : check for shell command delimiters */  
    if(check_shell_delimiter(command[parser_index])) {
        int state = get_shell_delimiter_state(command[parser_index]);
        parser_index++;
        return state;
    } 
    
    int token_index = 0;
    /* CASE 3 : extract the shell command */
    while(parser_index < n && !check_shell_delimiter(command[parser_index])) {
        token[token_index++] = command[parser_index++];
    }
    token[token_index] = '\0';
    return COMMAND;    
}

/* FSM for handling the command */
void command_handler(char *command_token) {
    char token[128];                            /* stores string token */
    char file_name[128];                        /* stores the file name */
    int pfd[2], fd;                             /* stores file descripters */
    ShellCommand shell_command;                 /* stores shell command */
    int current_state = START, next_state;      /* stores state of FSM */
    int num_process = 0;

    /* parse until the end of shell command */
    while(current_state != END) {
        /* get next token */
        next_state = parser(token, command_token);
        /* switch state accordingly and take actions */
        switch(next_state) {
            case COMMAND: 
                switch(current_state) {
                    /* seeing the first command after starting */
                    case START:
                        /* extract the command and store the command */
                        strcpy(shell_command.command, token);
                        argument_parser(&shell_command);
                        break;
                    
                    /* seeing command after pipe before */
                    case PIPE:
                        /* extract the command and store the command */
                        strcpy(shell_command.command, token);
                        argument_parser(&shell_command);
                        /* close the write end of the pipe */
                        close(pfd[1]);
                        /* duplicate read fd with pipe read end */
                        dup2(pfd[0], STDIN_FILENO);
                        break; 
                    
                    /* seeing command after input redirect */ 
                    case INPUT_REDIRECT:
                        /* interrpret current token as file not command */ 
                        strcpy(file_name, strtok(token, " "));
                        fd = open(file_name, O_RDONLY);
                        if(fd == -1) {
                            eprintf("cannot open file !")
                            exit(errno);            /* TODO : think on handling this case */
                        }
                        dup2(fd, STDIN_FILENO);
                        break;

                    /* seeing command after output redirect */
                    case OUTPUT_REDIRECT:
                        /* interrpret current token as file not command */ 
                        strcpy(file_name, strtok(token, " "));
                        fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                        if(fd == -1) {
                            eprintf("cannot open file !")
                            exit(errno);            /* TODO : think on handling this case */
                        } 
                        dup2(fd, STDOUT_FILENO);
                        break;
    
                    /* seeing command after & symbol */
                    case NON_BLOCKING_COMMAND:
                        /* execute the previous command and extract then new command */
                        execute_non_blocking_shell_command(shell_command);
                        num_process++;
                        /* extract the command and store the command */
                        strcpy(shell_command.command, token);
                        argument_parser(&shell_command);
                        break;
                }
                break;
            case PIPE: 
                switch(current_state) {
                    /* seeing a pipe after previous command */
                    case COMMAND:  
                        /* create new pipe and close the read end of pipe 
                         * and execute the shell command 
                         */
                        execute_shell_command_with_pipe(shell_command, pfd);
                        num_process++;
                        break;

                    /* malicious user : need learn how write shell commands */
                    case INPUT_REDIRECT:
                        eprintf("syntax error near unexpected token `newline'");
                        break;

                    /* malicious user : need learn how write shell commands */
                    case OUTPUT_REDIRECT:
                        eprintf("syntax error near unexpected token `newline'");
                        break;

                    /* malicious user : need learn how write shell commands */
                    case START:
                        eprintf("syntax error near unexpected token `|'");
                        break;
                }
                break;
            case INPUT_REDIRECT: 
                switch(current_state) {
                    case PIPE:
                        eprintf("syntax error near unexpected token `|'");
                        break;
                    case START:
                        eprintf("syntax error near unexpected token `|'");
                        break;
                    case OUTPUT_REDIRECT:
                        eprintf("syntax error near unexpected token `|'");
                }
                break;
            case OUTPUT_REDIRECT: 
                switch(current_state) {
                    case PIPE:
                        eprintf("syntax error near unexpected token `newline'");
                        break;
                    case START:
                        eprintf("syntax error near unexpected token `newline'");
                        break;
                    case INPUT_REDIRECT:
                        eprintf("syntax error near unexpected token `newline'");
                        break;
                }
                break;
            case NON_BLOCKING_COMMAND:
                switch(current_state) {
                    case START:
                        eprintf("syntax error near unexpected token `|'");
                        break; 
                    case PIPE:
                        eprintf("syntax error near unexpected token `newline'");
                        break;
                    case INPUT_REDIRECT:
                        eprintf("syntax error near unexpected token `newline'");
                        break;
                }
                break;
            case END: 
                switch(current_state) {
                    /* empty string command */
                    case START:
                        break;
                    /* malicious user : need learn how write shell commands */
                    case PIPE:
                        eprintf("syntax error near unexpected token `|'");
                        break;
                    /* malicious user : need learn how write shell commands */
                    case INPUT_REDIRECT:
                        eprintf("syntax error near unexpected token `newline'");
                        break;
                    /* malicious user : need learn how write shell commands */
                    case OUTPUT_REDIRECT:
                        eprintf("syntax error near unexpected token `newline'");
                        break;
                    /* execute command such that it's non blocking for shell terminal */
                    case NON_BLOCKING_COMMAND:
                        execute_non_blocking_shell_command(shell_command);
                        exit(errno);
                    /* execute command such that it's blocking for shell terminal */
                    case COMMAND:
                        execute_non_blocking_shell_command(shell_command);
                        num_process++;
                        break;
                }
                break;
            default:
                break;
        } 
        current_state = next_state;
    }
    /* wait for all the concurrently running process to get over */
    for(int i = 0; i < num_process; i++) {
        wait(NULL);
    }    
    exit(errno);
}


/* function executes the simple shell command concurrently */
void execute_blocking_shell_command(ShellCommand shell_command) {
    
    int pid = fork();
    /* child process will execute command */
    if(pid == 0) {
        /* TODO : handling misleading shell command how to manage 
         *        synchronization in case of mutiple commands
         */
        execvp(shell_command.arguments[0], shell_command.arguments);
    } 
    /* parent process will be blocked ! */
    else {
        wait(NULL);  
    } 
}

/* function executes the simple shell command concurrently */
void execute_non_blocking_shell_command(ShellCommand shell_command) {
    
    int pid = fork();
    /* child process will execute command */
    if(pid == 0) {
        /* TODO : handling misleading shell command how to manage 
         *        synchronization in case of mutiple commands
         */
        execvp(shell_command.arguments[0], shell_command.arguments);
    } 
    /* parent process will be remain unblocked ! */
    else {
        return;
    } 
}


/* function executes the shell command connecting output to pipe */
void execute_shell_command_with_pipe(ShellCommand shell_command, int pfd[]) {
    pipe(pfd);
    int pid = fork();
    if(pid == 0) {
        /* close the read end and duplicate the STDOUT with write end */
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
        /* TODO : handling misleading shell command how to manage 
         *        synchronization in case of mutiple commands
         */
        execvp(shell_command.arguments[0], shell_command.arguments); 
    } else {
        /* this makes commands in pipe to execute concurrently */
        return;
    }
}


