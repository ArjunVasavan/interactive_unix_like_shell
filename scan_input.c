#include "header.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
void scan_input(char *prompt, char *input_string) {

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

    }
}
