#include <stdio.h>
#include <stdlib.h>
#include "includes/io.h"
#include "includes/lex.h"
#include "includes/parse.h"


int main(int argc, char* argv[]) {
    char* file_contents = read_file(argv[1]);
    lex_state* lex_state = lex_init(file_contents);
    parse_state* parse_state = parse_init(lex_state);
    token* tok;

    parse_parse(parse_state);

    free(lex_state);
    free(parse_state);
    free(file_contents);

    return 0;
};
