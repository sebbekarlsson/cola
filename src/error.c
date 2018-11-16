#include "includes/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void error(char* msg) {
    printf(msg);
    printf("\n");
    exit(-1);
}

void error_in_lexer(char* msg) {
    printf("Error in lexer:\n");
    error(msg);
}

void error_in_parser(char* msg) {
    printf("Error in parser:\n");
    error(msg);
}

void error_in_interpreter(char* msg) {
    printf("Error in interpreter:\n");
    error(msg);
}
