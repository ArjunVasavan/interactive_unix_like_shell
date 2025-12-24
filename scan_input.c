#include "header.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
void scan_input(char *prompt, char *input_string) {

    //TODO: call extract_external_command();
    //declare an 2d array *ext_command[][] which should be fs2d
    //and pass it to extract_external_command function

    while (true) {

        printf("%s",prompt);

        scanf("%[^\n]",input_string);

        getchar(); // Clearing the buffer

        if ( strncmp(input_string,"PS1=",4) == 0 ) {

            if ( input_string[4] != ' ' ) {

                strcpy(prompt,input_string+4); // copies from 4th address

            } else {

                // TODO: print ERROR message

            }

        }

        //TODO: call char* command = get_command(input);
        // int type = check_command_type(command);
        // if ( type is BULT ) {
        // logic 
        //  
        //  call  exec_internal_command(char* input)
        //
        //
        // } else if ( type is EXTERNAL ) {
        // logic
        //}

    }


}
