#include "header.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void scan_input(char *prompt, char *input_string) {

    char* external_commands[153];

    extract_external_commands(external_commands);

    extern int external_commands_count;

    for ( int i = 0 ; i < external_commands_count ; i++ ) {

        printf("%s\n",external_commands[i]);

    }

    while (true) {

        printf("%s",prompt);

        scanf("%[^\n]",input_string);

        getchar(); // Clearing the buffer

        //FIXME : left to do it at last for doing PS1 operation

        if ( strncmp(input_string,"PS1=",4) == 0 ) {

            if ( input_string[4] != ' ' ) {

                strcpy(prompt,input_string+4); // copies from 4th address

            } else {

                // print ERROR message

            }

        }

        //TODO: call char* command = get_command(input);
        // int type = check_command_type(command);
        // if ( type is BULT ) {
        // logic 
        //  call  exec_internal_command(char* input)
        // } else if ( type is EXTERNAL ) {
        // logic
        //}

        char* command = get_command(input_string);

        if ( command == NULL ) {

            perror("[ERROR] < get_command > founded ' ' at beginning ");

        }
        printf("Command returned is %s\n",command);

        //TODO int type = check_command_type(command);
        

        free(command);
    }


}
