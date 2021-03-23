#ifndef LOG_H
#define LOG_H 1

/* prints the prompt on console             */
#define PRINT_PROMPT(curr_dir)                                      \
        printf("\n%s\n ISHELL > ", curr_dir);                       \

/* print the error message on the terminal  
 * advisible to use in case of fork and exec
 */
#define PRINT_ERR(msg, ...)                                         \
    fprintf(stderr,"IRON-shell : " msg                              \
            "\nfile = %s, line number = %d, in function = %s()\n"   \
            ##__VA_ARGS__, __FILE__, __LINE__, __func__);           \
    exit(errno);                                                    \


/* prints the exeption message on the shell */
#define PRINT_EXECPTION(msg)                                        \
    fprintf(stderr, "IRON-shell :" msg "\n")


/* prints the head of the jobs */
#define PRINT_JOB_PROCESS_HEAD(id, pid, pname, msg_stat)            \
    fprintf(stdout, "\n [%d]\t+ %d " msg_stat "\t%s\n",             \
                    id, pid, pname);                                \
  

/* prints any process node from job (not the head)  */
#define PRINT_JOB_PROCESS_NODE(pid, pname, msg_stat)                \
    fprintf(stdout, "     \t+ %d " msg_stat "\t%s\n",               \
                    pid, pname);                            


/* prints the job ones it is done and exitied */
#define PRINT_JOB_DONE(id, pid, pname)                              \
    fprintf(stdout, "\n [%d]  +  Done  %d\t%s\n", id, pid, pname);  \


#endif /* LOG_H */
