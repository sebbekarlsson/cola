#include <stdio.h>
#include <stdlib.h>
#include "includes/io.h"
#include "includes/lex.h"
#include "includes/scope.h"
#include "includes/parse.h"
#include "includes/interpret.h"
#include "includes/default_scope_initialize.h"


scope* global_scope;

int main(int argc, char* argv[]) {
    global_scope = init_scope();

    default_scope_initialize(global_scope);

    char* file_contents = read_file(argv[1]);
    lex_state* lex_state = lex_init(file_contents);
    parse_state* parse_state = parse_init(lex_state);

    ast_node* tree = (ast_node*) parse_parse(parse_state, (void*)0);
    interpret_visit(tree);

    free(tree);
    free(lex_state);
    free(parse_state);
    free(file_contents);

    return 0;
};
