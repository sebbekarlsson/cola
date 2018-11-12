#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* char_to_string(char c) {
    char* str;
    str = malloc(sizeof(char) * 2);
    str[0] = c;
    str[1] = '\0';

    return str;
};
