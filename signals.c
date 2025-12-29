#include "header.h"

void signal_handler(int signum ) {

    extern char prompt[25];

    if ( signum == SIGINT ) { // ctrl+c

        printf("%s",prompt);

    } else if ( signum == SIGTSTP ) { // ctrl+z
        
        printf("%s",prompt);
    
    }
}

//TODO: SIGNAL PART
//
//  ctrl + c => code should not be terminated it should print new prompt
//
//NOTE: the thing is prompt and input string array should be global else 
//       you cannot access it on siganl_handler function 
//
//ERROR : use waitpid(pid,&status,WUNTRACED); idk where to put it 
//
//  siganl_handler( signum ) {
//
//      if ( collected siganal is SIGINT ) {
//
//          print(prompt);
//          
//      } else if ( collected signal is Ctrl+z ) {
//              
//              print(prompt);
//      } 
//
//  }
