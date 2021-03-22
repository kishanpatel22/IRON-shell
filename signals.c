#include "signals.h"
#include "global.h"
#include "job.h"

/* default signal hanlder which manages all the signals for the main shell  */
void signal_handler(int signo) {
    
    /* control-C will kill the currently running foreground job             */
    if(signo == SIGINT) {
        kill_job(&(iscb.fg_job));
    } 

    /* control-Z will suspend the currently running job and will add the 
     * the parituclar job context in list of suspened and running jobs.
     */
    else if(signo == SIGTSTP) {
        
        /* suspened the current jobs i.e. stop its execution            */
        suspend_job(&(iscb.fg_job)); 
        
        /* add the job the list of suspened / running jobs maintained   */
        add_job(&(iscb.jobs), iscb.fg_job);

        /* initialize the job again for new foreground job in shell     */
        init_job(&(iscb.fg_job), "");
        
    } 

    /* SIGCHILD will inform the shell about the completion of the child process 
     * the shell will free the dynamically allocated resource regarding 
     * particular process which was part of the job
     */
    else if(signo == SIGCHLD) {
        pid_t pid = waitpid(-1, 0, WNOHANG);

        if(pid == -1 || pid == 0) {
            return;
        }
        /* delete the job with the given pid */
        delete_job(&(iscb.jobs), pid);
    }

    return;
}

/* adds the user defined shell signals  */
void set_signals() {
    signal(SIGINT, signal_handler); 
    signal(SIGTSTP, signal_handler); 
    signal(SIGCHLD, signal_handler); 
}

/* reset to default signals */
void reset_signals() {
    signal(SIGINT, SIG_DFL);
    signal(SIGSTOP, SIG_DFL);
    signal(SIGCHLD, signal_handler); 
}

