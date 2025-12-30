#include "header.h"

char prompt[25] = "Minishell: "; // this will be printed on cli
char input_string[25];

int main(int argc, char** argv) {

    system("clear"); //  clears the CLI
    scan_input(prompt,input_string); 

}
