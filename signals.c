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

/*
 TODO: ctrl+z signal handler

 declare an structure struct strop arr[50]; -> whenever we presss ctrl+z we have to store it
 inside signal handler we store this 

 if ( signum == SIGTSTP ) {
    
    if ( pid == 0 ) {
        
        print the minishell prompt

    } else {
        
        store it

        for continuing the process you need pid 

        int index => global

        arr[index].spid = pid;

        strcpy(arr[index].name,input_string);

        index+=1;
    }
 }
*/ 

