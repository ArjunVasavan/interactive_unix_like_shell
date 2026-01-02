#include "header.h"

char prompt[25] = "Minishell: "; // this will be printed on cli as default
char input_string[25];

int main(int argc, char** argv) {

    system("clear"); //  clears the CLI at initial

    scan_input(prompt,input_string);

}

// NOTE: ctrl+z bug fix is that dont use make run there use ./a.out
