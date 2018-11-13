#include <stdio.h>
#include <stdlib.h>
#include "includes/io.h"
#include "includes/lex.h"
#include "includes/parse.h"
#include "includes/interpret.h"


int main(int argc, char* argv[]) {
    char* file_contents = read_file(argv[1]);
    lex_state* lex_state = lex_init(file_contents);
    parse_state* parse_state = parse_init(lex_state);

    ast_node* tree = (ast_node*) parse_parse(parse_state);
    interpret_visit(tree);

    free(tree);
    free(lex_state);
    free(parse_state);
    free(file_contents);

    return 0;
};
