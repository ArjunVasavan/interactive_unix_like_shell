#include "header.h"
#include <stdio.h>
#include <string.h>

char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
    "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
    "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help","fg","bg","jobs",NULL };

int external_commands_count = 0;

pid_t pid;

void pipe_operation(char *input_string) {
    char input_copy[1024];
    

    pipe_alligner(input_string);

    strncpy(input_copy, input_string, sizeof(input_copy) - 1);
    input_copy[sizeof(input_copy) - 1] = '\0';
    char *argv[100];
    int argc = 0;
    char *token = strtok(input_copy, " ");

    while (token != NULL) {

        argv[argc++] = token;
        token = strtok(NULL, " ");

    }

    argv[argc] = NULL;
    int command_index[50];
    int total_pipe_count = 0;
    int cmd_count = 0;
    command_index[cmd_count++] = 0;

    for (int i = 0; i < argc; i++) {

        if (strcmp(argv[i], "|") == 0) {

            argv[i] = NULL;   // terminate previous command
            command_index[cmd_count++] = i + 1;
            total_pipe_count++;

        }

    }

    int pipes[total_pipe_count][2];

    for (int i = 0; i < total_pipe_count; i++) {

        if (pipe(pipes[i]) == -1) {

            perror("pipe");
            exit(EXIT_FAILURE);

        }

    }

    pid_t pids[50];   // store child PIDs for waitpid

    for (int i = 0; i <= total_pipe_count; i++) {

        pid_t pid = fork();
        pids[i] = pid;

        if (pid == -1) {

            perror("fork");
            exit(EXIT_FAILURE);

        }

        if (pid == 0) {  // Child process

            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);

            if (i > 0) {

                dup2(pipes[i - 1][0], STDIN_FILENO);

            }

            if (i < total_pipe_count) {

                dup2(pipes[i][1], STDOUT_FILENO);

            }

            for (int j = 0; j < total_pipe_count; j++) {

                close(pipes[j][0]);
                close(pipes[j][1]);

            }

            execvp(argv[command_index[i]], &argv[command_index[i]]);
            perror("execvp");
            exit(EXIT_FAILURE);

        }

    }

    for (int i = 0; i < total_pipe_count; i++) {

        close(pipes[i][0]);
        close(pipes[i][1]);

    }

    int pipe_status;

    for (int i = 0; i <= total_pipe_count; i++) {

        waitpid(pids[i], &pipe_status, WUNTRACED);

        if (WIFSTOPPED(pipe_status)) {
            // Pipeline stopped by Ctrl+Z
            // Shell should regain control
            break;
        }

    }

}


int pipecheck(char* input_string ) {

    int i = 0;

    

    while (input_string[i]) {

        if ( input_string[i] == '|' )

            return 1;  // PIPE is present

        i+=1;
    }

    return 0; // PIPE is not present

}


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

            if (external_commands_count < 155) {   

                int len = strlen(temp_buff);

                external_commands[external_commands_count] =
                    malloc((len + 1) * sizeof(char));

                strcpy(external_commands[external_commands_count], temp_buff);
                external_commands_count++;

            }

            i = 0;
        }
    }

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

char *get_command(char *input_string) {

    char tmp_buff[1024];
    int i = 0;

    // if (input_string[0] == ' ') return NULL;

    while (input_string[i] != ' ' &&
        input_string[i] != '\0' &&
        i < 1023) {

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

void execute_external_commands(char *input_string,char* command ) {

    signal(SIGINT,SIG_DFL);
    signal(SIGTSTP,SIG_DFL);

    char input_copy[1024];

    strncpy(input_copy, input_string, sizeof(input_copy) - 1);

    input_copy[sizeof(input_copy) - 1] = '\0';

    char *argv[20];

    int i = 0;

    argv[i++] = command;

    char *args = input_copy + strlen(command);

    while (*args == ' ') args++;

    char *token = NULL;

    if (*args != '\0')
        token = strtok(args, " ");

    while (token != NULL && i < 19)
    {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }

    argv[i] = NULL;

    input_string[0] = '\0';

    execvp(argv[0],argv);

    perror("execvp");

    exit(1);
}

void execute_internal_commands(char *input_string) {

    if ( strncmp(input_string,"exit",4) == 0 ) {
        exit(0);
    } else if ( strncmp(input_string,"pwd",3) == 0 ) {

        char buff[550];

        if(getcwd(buff,sizeof(buff) ) == NULL ) {

            perror("getcwd");
            exit(1);
        }

        printf("PATH: %s\n",buff);

    } else if ( strncmp ( input_string , "cd" , 2) == 0  ) {

        char *path = input_string + 3;   // after "cd "

        if (chdir(path) != 0) {
            perror("cd");
        }

    } else if ( strncmp(input_string, "help" , 4 ) == 0 ) {

        printf("[USER GUIDE]: \n"); 

    error_case:
        printf("which commands you want to see : \n");
        printf("1. Builtin \n2. External \nEnter your choice : ");
        int choice;
        scanf("%d",&choice);

        switch (choice) {

            case 1: {

                printf("Built-in commands:\n");
                for (int i = 0; builtins[i] != NULL; i++)
                {
                    printf("  %-10s\n", builtins[i]);
                }

                break;
            }

            case 2: {

                extern char* external_commands[155]; 
                int i = 0;
                printf("External commands:\n");

                while(external_commands[i] != NULL) {

                    printf("  %-10s\n",external_commands[i]);
                    i+=1;
                }

                break;
            }

            default:{
                printf("[ERROR]: Enter 1 or 2 \n");
                goto error_case;
            }

        }

        // FIXME: repeated command printing bug
        // i solved this bug using __fpurge
        // the confusion is that if i use fflush it wont work
        __fpurge(stdin);

    } else if ( strncmp(input_string,"echo $$",7) == 0 ) {

        printf("%d\n",getpid());

    } else if ( strcmp(input_string,"echo $?") == 0 ) {

        /*
        NOTE: echo $? => exit status of last foreground command.
        WIFSIGNALED   => true if killed by signal else false
        WTERMSIG      => which signal killed the process
        WTERMSIG+128  => POSIX conversion for echo $? 
        WIFEXITED     => child process terminated normally or not?
        WEXITSTATUS   => exit code returned by child
        0             => success/nothing went wrong
        */

        extern int status;

        if (WIFEXITED(status)) { // command exited normally?
            printf("%d\n", WEXITSTATUS(status));  // exit code returned by child
        }
        else if (WIFSIGNALED(status)) { // is child terminated by signal?
            printf("%d\n", 128 + WTERMSIG(status)); 

        }
        else {
            printf("0\n");
        }
    } else if ( strcmp(input_string,"echo $SHELL") == 0 ) {

        printf("%s\n",getenv("SHELL"));

    } else if ( strcmp(input_string,"jobs") == 0 ) {

        extern int signal_details_index;
        extern Stop signal_details[50];

        for ( int i = 0 ; i < signal_details_index ; i++ ) {

            printf("[%d] %s\n",i+1,signal_details[i].name);

        }

    } else if ( strcmp(input_string,"fg") == 0 ) {

        extern int signal_details_index;
        extern Stop signal_details[50];

        if (signal_details_index == 0) {
            printf("fg: no current job\n");
            return;
        }

        int job_index = signal_details_index - 1;

        // NOTE: for continuing processes we use KILL

        kill(signal_details[job_index].spid,SIGCONT);

        // TODO: DSA is needed to implemented here

        waitpid(signal_details[job_index].spid,NULL,WUNTRACED);

        // Remove from array by shifting all elements after it

        for (int i = job_index; i < signal_details_index - 1; i++) {
            signal_details[i] = signal_details[i + 1];
        }

        signal_details_index--;

    } else if ( strcmp(input_string,"bg") == 0 ) {

        extern int signal_details_index;
        extern Stop signal_details[50];

        if (signal_details_index == 0) {
            printf("bg: no current job\n");
            return;
        }

        int job_index = signal_details_index - 1;

        signal(SIGCHLD,signal_handler);

        kill(signal_details[job_index].spid,SIGCONT);

        // NOTE: SIGCHLD handler remove it when process finishes

    }


}
