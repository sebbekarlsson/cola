#include <stdio.h>
#include <stdlib.h>
#include "includes/io.h"
#include "includes/lex.h"


int main(int argc, char* argv[]) {
    char* file_contents = read_file(argv[1]);
    lex_state* state = lex_init(file_contents);
    token* tok; 

    while (1) {
        tok = lex_get_next_token(state);

        if (tok->type == _EOF) {
            free(tok);
            break;
        }

        printf("Token(%d, %s)\n", tok->type, tok->value);

        free(tok->value);
        free(tok);
    }

    free(state);
    free(file_contents);

    return 0;
};
