#include "command_handler.h"
#include "buildin.h"

#define MAX_DIR_LENGHT (512)


int main(int argc, char *argv[]) {
    
    /* holds muliple commands entered as single string */
    char command_buffer[MAX_COMMAND_LENGHT];
    char current_working_dir[MAX_DIR_LENGHT];
    char *home = getenv("HOME");

    /* main loop for the shell prompt */
    while(1) {
        /* shell prompt being logged on screen with every command */
        getcwd(current_working_dir, 512);
        printf("\n%s\n \u2192 ", current_working_dir); 

        if(read_command(command_buffer, MAX_COMMAND_LENGHT) != EOF) {
            /* check if its build in shell command */
            if(check_buildin_command(command_buffer)) {
                execute_shell_buildin_command(command_buffer); 
            } 
            /* if not build in shell command */
            else {
                int pid = fork();
                switch(pid) {
                    /* child process */
                    case 0:
                        /* command handler is invoked */
                        command_handler(command_buffer);
                        wait(NULL);  
                        break;
                    /* can't fork child process */
                    case -1:
                        printf("fork failure !\n");
                        exit(errno);
                        break;
                    /* parent process */
                    default:
                        wait(0);
                        break;
                }
            }
        } else {
            /* exit as user pressed control-D */
            break;
        }
    }
    return 0;
}
