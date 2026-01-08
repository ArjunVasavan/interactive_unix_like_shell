#include "header.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void inital_space_handling( char* input_string ) {
    while ( 1 ) {
        if  ( input_string[0] == ' ' ) {
            int i = 0;
            while (input_string[i]) {
                input_string[i] = input_string[i+1];
                i+=1;
            }
        } else {
            printf("Result is %s\n",input_string);
            printf("Size is %lu\n",strlen(input_string));
            return;
        }
    }
}

// TODO: pipe fault example : ls|ls|ls bug
//
// void pipe_alligner( char* input_string ) {
//
//     int i = 1;
//
//     while ( input_string[i] ) {
//
//         if ( input_string[i] != ' ' && input_string[i+1] == '|' ) {
//
//             int j = i;
//
//
//
//         }
//
//
//         i+=1;
// }
//
// }
