#include "global.h"

int main(int argc, char *argv[]) {
    
    /* holds the commands entered as single string  */
    char command_buffer[MAX_COMMAND_SIZE];

    /* the name of the current working directory    */
    char current_working_dir[MAX_DIR_LENGHT];
    
    /* initialize the iron shell control block      */
    init_shell_control_block(&iscb);

    /* main loop for the iron-shell prompt          */
    while(1) {

        /* shell prompt being logged on screen with every command */
        getcwd(current_working_dir, 512);
        PRINT_PROMPT(current_working_dir);

        if(read_command(command_buffer, MAX_COMMAND_SIZE) != EOF) {
            /* check if its build in shell command */
            if(check_builtin_command(command_buffer)) {
                execute_shell_builtin_command(command_buffer); 
            } 
            /* if not build in shell command */
            else {
                /* command handler handles the execution of the user commmand */
                command_handler(command_buffer);
            }
        } else {
            /* exit as user pressed control-D */
            break;
        }
    }
    return 0;
}
