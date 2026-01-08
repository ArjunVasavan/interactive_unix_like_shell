#include "header.h"
#include <stdio.h>
#include <string.h>

char* external_commands[155];
int status;

void scan_input(char *prompt, char *input_string) {

    signal(SIGINT,signal_handler); // print prompt only on ctrl + c
    signal(SIGTSTP,signal_handler); // print prompt only on ctrl + z

    extract_external_commands(external_commands);

    extern int external_commands_count;

    while (true) { 

        printf(
            "\033[1;36m%s"
            "\033[01;33m$ "
            "\033[0m",
            prompt
        );

        input_string[0] = '\0'; // clearing buffer first 
        int scan_ret = scanf("%1023[^\n]",input_string);
        getchar(); // Clearing the buffer
        
        if ( scan_ret == EOF ) {

            printf("[ERROR]: out of bound signal is used\n");
            exit(1);

        }

        if ( input_string[0] == ' ' ) {

            inital_space_handling(input_string);

        }

        if ( pipecheck(input_string) ) {
            pipe_alligner(input_string);
        }

        if ( strncmp(input_string,"PS1=",4) == 0 ) {

            if ( input_string[4] != ' ' ) {

                strcpy(prompt,input_string+4); // copies from 4th address

            } else {

                perror("PS1");

            }

        } else {    

            char* command = get_command(input_string);

            if ( command == NULL ) {

                fprintf(stderr,"[ERROR] from get_command \n");

                goto error_handling_command;
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

                    if ( strlen(command) != 0 ) {
                        printf("%s: command not found\n",command);
                    }
                    break;

                }

                default: {

                    printf("[EDGE CASE]: reached default\n");

                }

            }

        error_handling_command:
            free(command);

        }
    }
}
