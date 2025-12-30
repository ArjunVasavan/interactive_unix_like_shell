#include "header.h"

void signal_handler(int signum ) {

    extern char prompt[25];

    extern pid_t pid;

    if ( signum == SIGINT ) { // ctrl+c

        
        if ( pid == 0 ) {

            printf("\033[1;36m");
            printf("\n%s\n",prompt);
            printf("\033[01;33m");

        }


    } else if ( signum == SIGTSTP ) { // ctrl+z
        
        if ( pid == 0 ) {

            printf("\033[1;36m");
            printf("\n%s\n",prompt);
            printf("\033[01;33m");

        }
    
    }
}
