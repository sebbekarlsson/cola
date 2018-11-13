#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


char* char_to_string(char c) {
    char* str;
    str = malloc(sizeof(char) * 2);
    str[0] = c;
    str[1] = '\0';

    return str;
};

int is_integer(char* str) {
    for (int i = 0; i < strlen(str); i++)
        if (!isdigit(str[i]))
            return 0;

    return 1;
};
