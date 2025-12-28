#include "header.h"
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include<stdio.h>
#include <unistd.h>
char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
    "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
    "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL };


//TODO: call extract_external_command function 
// 1-> read till \n
// 2-> allocate memory according to column based on length of command
// 3-> store the command to 2d array
// do this till NULL

int external_commands_count = 0; // NOTE Use EXTERN to collect this on that other file

void extract_external_commands(char **external_commands) {

    int fd = open("external_commands.txt",O_RDONLY);

    char char_buff; // to collect each character by character

    char temp_buff[30]; // to store when running inside loop
    int i = 0;


    while ( read(fd,&char_buff,1) != 0 ) {


        if ( char_buff != '\n' ) {

            temp_buff[i] = char_buff;

            i+=1;

        } else {

            temp_buff[i] = '\0';

            int len = strlen(temp_buff);

            external_commands[external_commands_count] = (char*)malloc(len+1 * (sizeof(char)));

            strcpy(external_commands[external_commands_count],temp_buff);

            external_commands_count+=1;

            i = 0;
        }

    }

}

//TODO: get_command();
//
//get_command(intput) -> 
// this will return the command first till ' '
// create an array
// at the end put \0 char 
// EXAMPLE: [l][s][\0]
//
//  
//

//TODO: int check_command_type (char* ) {
//
// for ( loop till NULL) {
//      
//      if ( cmd == builtin[i]){
//      return MACRO of BUILTIN
//      }
//
//      like wise do it 
//
// }
//
//}


//TODO: void extract_external_command(char* input ) {
//
//          
//
//}


//TODO: void extract_internal_command(char* input ) { used for BUILTIN
//          
//          if ( input ==  exit ) {
//              
//              exit(0);
//
//          } else if ( input == pwd ) {
//             
//             call getcwd() function
//             1. declare buffer[50];
//             2. getcwd(buffer,50);
//             printf("%s\n",buffer);
//             // for doing pwd theres an function 
//
//          } else if ( input == cd ) {
// 
//              eg: input -> cd newdir
//
//              use strncmp to get newdir
//
//              call chdir function
//              chdir(PATH which is input+3 {c d <space> => 3 });
//
//              use getcwd to confirm path is reached
//              
//          }
//          
//}
