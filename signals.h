#ifndef SIGNALS_H
#define SIGNALS_H 1

#include <sys/types.h>
#include <sys/wait.h>

/* adds the user defined signals  */
void set_signals();

/* reset to default signals */
void reset_signals();

/* default signal hanlder which manages all the signals for the main shell  */
void signal_handler(int signo);

#endif /* SIGNALS_H */
