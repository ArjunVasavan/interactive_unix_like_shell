#include "header.h"

void inital_space_handling( char* input_string ) {

    while ( 1 ) {

        if  ( input_string[0] == ' ' ) {

            int i = 0;
            while (input_string[i]) {

                input_string[i] = input_string[i+1];
                i+=1;

            }

        } else {

            return;

        }
    }
}


void pipe_alligner(char *input_string) {

    char temp_buff[1024];
    int i = 0, j = 0;

    while (input_string[i] && j < sizeof(temp_buff) - 1) {

        if (input_string[i] == '|' &&
            j > 0 &&
            temp_buff[j - 1] != ' ') {
            temp_buff[j++] = ' ';
        }

        temp_buff[j++] = input_string[i];

        if (input_string[i] == '|' &&
            input_string[i + 1] &&
            input_string[i + 1] != ' ') {
            temp_buff[j++] = ' ';
        }

        i++;
    }

    temp_buff[j] = '\0';
    strcpy(input_string, temp_buff);

}
