#include "header.h"

char* external_commands[155];

void scan_input(char *prompt, char *input_string) {

    extract_external_commands(external_commands);

    extern int external_commands_count;

    while (true) {


        printf("\033[1;36m");
        printf("%s",prompt);
        printf("\033[01;33m");
        printf("$ ");
        printf("\033[0m");

        scanf("%24[^\n]",input_string);

        getchar(); // Clearing the buffer

        //FIXME : left to do it at last for doing PS1 operation

        if ( strncmp(input_string,"PS1=",4) == 0 ) {

            if ( input_string[4] != ' ' ) {

                strcpy(prompt,input_string+4); // copies from 4th address

            } else {

                // print ERROR message

            }

        }

        char* command = get_command(input_string);

        if ( command == NULL ) {

            perror("[ERROR] < get_command > founded ' ' at beginning ");

        }

        int type = check_command_type(command);

        switch (type) {

            case BUILTIN: {

                execute_internal_commands(input_string);

                break;
            }

            case EXTERNAL: {

                execute_external_commands(input_string,command);

                break;
            }

            case NO_COMMAND: {

                printf("No command\n");

                break;
            }
            default:{
                printf("reached default\n");
            }

        }

        free(command);
    }
}
