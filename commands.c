#include<stdio.h>
char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
    "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
    "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL };


//TODO: call extract_external_command function 
// 1-> read till \n
// 2-> allocate memory according to column based on length of command
// 3-> store the command to 2d array
// do this till NULL


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
