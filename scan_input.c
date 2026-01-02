#include "header.h"

char* external_commands[155];

int status;

void scan_input(char *prompt, char *input_string) {

    signal(SIGINT,signal_handler); // Interruput
    signal(SIGTSTP,signal_handler); // Signal Termination Stop

    extract_external_commands(external_commands);

    extern int external_commands_count;

    while (true) {

        printf("\033[1;36m");
        printf("%s",prompt);
        printf("\033[01;33m");
        printf("$ ");
        printf("\033[0m");

        input_string[0] = '\0'; // clearing buffer first 
        scanf("%24[^\n]",input_string);
        getchar(); // Clearing the buffer

        // DONE: PS1 operation

        if ( strncmp(input_string,"PS1=",4) == 0 ) {

            if ( input_string[4] != ' ' ) {

                strcpy(prompt,input_string+4); // copies from 4th address

            } else {

                // print ERROR message
                perror("PS1");

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

                if ( pipecheck(input_string) ) {

                    pipe_operation(input_string);

                } else {

                    extern pid_t pid;

                    pid = fork();

                    if ( pid == 0  ) {

                        signal(SIGINT,SIG_DFL);
                        signal(SIGTSTP,SIG_DFL);

                        execute_external_commands(input_string,command);

                        exit(1);

                    } else {
                    
                        waitpid(pid, &status, WUNTRACED);

                        // NOTE: UNTRACED: eventhough child is getting [stopped] we clear the resorces of child
                        
                        pid = 0;

                    }

                }

                break;
            }

            case NO_COMMAND: {

                printf("%s: command not found\n",command);

                break;
            }

            default: {

                printf("[EDGE CASE]: reached default\n");

            }

        }

        free(command);
    }
}
