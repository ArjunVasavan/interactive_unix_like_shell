#include "header.h"
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

Stop signal_details[50];
int signal_details_index = 0;

void signal_handler(int signum) {
    extern char prompt[25];
    extern pid_t pid;

    if (signum == SIGINT) { // ctrl+c
        if (pid == 0) {
            printf(
                "\n\033[1;36m%s\n"
                "\033[01;33m$ "
                "\033[0m",
                prompt
            );
            fflush(stdout);
        }
    } else if (signum == SIGTSTP) { // ctrl+z
        if (pid == 0) { // at child process
            printf(
                "\n\033[1;36m%s\n"
                "\033[01;33m$ "
                "\033[0m",
                prompt
            );
            fflush(stdout);
        } else { // during parent process ctrl+z is called
            extern char input_string[25];
            signal_details[signal_details_index].spid = pid;
            strcpy(signal_details[signal_details_index].name, input_string);
            signal_details_index += 1;
        } 
    } else if (signum == SIGCHLD) {
        int status;
        pid_t terminated_pid = waitpid(-1, &status, WNOHANG);

        if (terminated_pid > 0) {
            // Find and remove the terminated process from array
            for (int i = 0; i < signal_details_index; i++) {
                if (signal_details[i].spid == terminated_pid) {
                    // Shift all elements after it down
                    for (int j = i; j < signal_details_index - 1; j++) {
                        signal_details[j] = signal_details[j + 1];
                    }
                    signal_details_index--;
                    break;
                }
            }
        }
    }
}
