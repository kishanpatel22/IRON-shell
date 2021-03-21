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

    return;
}

/* adds the user defined shell signals  */
void set_signals() {
    signal(SIGINT, signal_handler); 
    signal(SIGTSTP, signal_handler); 
}

/* reset to default signals */
void reset_signals() {
    signal(SIGINT, SIG_DFL);
    signal(SIGSTOP, SIG_DFL);
}

