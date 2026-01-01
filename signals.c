#include "header.h"
#include <signal.h>
#include <string.h>

Stop signal_details[50];

int signal_details_index = 0;

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

        if ( pid == 0 ) { // at child process

            printf("\033[1;36m");
            printf("\n%s\n",prompt);
            printf("\033[01;33m");

        } else { // during parent process ctrl+z is called

            extern char input_string[25];

            signal_details[signal_details_index].spid = pid;

            strcpy(signal_details[signal_details_index].name,input_string);

            signal_details_index+=1;
        } 

    } else if ( signum == SIGCHLD ) {

        int status;
        waitpid(-1,&status,WNOHANG);

        // NOTE: WNOHANG: if any child terminates it ill immediatly return
        //-1 => for any process

    }
}

