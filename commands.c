#include "header.h"
#include <stdio.h>

char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
    "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
    "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL };


int external_commands_count = 0; // NOTE Use EXTERN to collect this on that other file

void extract_external_commands(char **external_commands) {

    int fd = open("external_commands.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    char char_buff;
    char temp_buff[100];
    int i = 0;

    while (read(fd, &char_buff, 1) > 0) {

        if (char_buff != '\n') {

            if (i < 99) {                 //  bound check
                temp_buff[i++] = char_buff;
            }

        } else {

            temp_buff[i] = '\0';

            if (external_commands_count < 155) {   // bound check
                int len = strlen(temp_buff);
                external_commands[external_commands_count] =
                    malloc((len + 1) * sizeof(char));   // fixed malloc

                strcpy(external_commands[external_commands_count], temp_buff);
                external_commands_count++;
            }

            i = 0;
        }
    }

    /*  handle last line if no newline */
    if (i > 0 && external_commands_count < 155) {
        temp_buff[i] = '\0';
        int len = strlen(temp_buff);
        external_commands[external_commands_count] =
            malloc((len + 1) * sizeof(char));
        strcpy(external_commands[external_commands_count], temp_buff);
        external_commands_count++;
    }

    close(fd);
}

// BUG : stack smash error was happening on here
char *get_command(char *input_string) {

    char tmp_buff[100];
    int i = 0;

    if (input_string[0] == ' ')
        return NULL;

    while (input_string[i] != ' ' &&
           input_string[i] != '\0' &&
           i < 99) {
        tmp_buff[i] = input_string[i];
        i++;
    }

    tmp_buff[i] = '\0';

    char *ret_buff = malloc(strlen(tmp_buff) + 1);
    strcpy(ret_buff, tmp_buff);

    return ret_buff;
}


int check_command_type(char *command) {

    extern int external_commands_count;

    extern char* external_commands[155]; 

    int i = 0;

    while (builtins[i] != NULL) {

        if ( strcmp(command,builtins[i]) == 0 ) {

            return BUILTIN; // which is 1

        }

        i+=1;
    }


    for ( int i = 0 ; i < external_commands_count ; i++ ) {

        if (strcmp(external_commands[i],command) == 0 ) {

                    return EXTERNAL;

        }
    }

    return NO_COMMAND;
}

//TODO: void extract_external_command(char* input ) {
//
//          
//
//}


//TODO: void extract_internal_command(char* input ) { used for BUILTIN
//          if ( input ==  exit ) {
//              exit(0);
//          } else if ( input == pwd ) {
//             call getcwd() function
//             1. declare buffer[50];
//             2. getcwd(buffer,50);
//             printf("%s\n",buffer);
//             // for doing pwd theres an function 
//          } else if ( input == cd ) {
//              eg: input -> cd newdir
//              use strncmp to get newdir
//              call chdir function
//              chdir(PATH which is input+3 {c d <space> => 3 });
//              use getcwd to confirm path is reached
//          }
//}

//BUG sometimes stack smashing is happening 
void execute_internal_commands(char *input_string) {

    printf("Input string is %s\n",input_string);
    if ( strncmp(input_string,"exit",4) == 0 ) {
        exit(0);
    } else if ( strncmp(input_string,"pwd",3) == 0 ) {

        char buff[50];

        getcwd(buff,50);

        printf("PATH: %s\n",buff);
    
    } else if ( strncmp ( input_string , "cd" , 2) ) {
    


    }

}
