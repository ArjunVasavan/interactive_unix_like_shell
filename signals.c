#include "header.h"

void signal_handler(int signum ) {

    extern char prompt[25];

    if ( signum == SIGINT ) { // ctrl+c

        printf("\n");

    } else if ( signum == SIGTSTP ) { // ctrl+z
        
        printf("\n");
    
    }
}

