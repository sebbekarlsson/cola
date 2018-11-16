#include <stdlib.h>
#include "includes/ast_node_variable.h"


ast_node_variable* init_ast_node_variable(token* tok, ast_node_variable_definition* definition) {
    ast_node_variable* ast;
    ast = calloc(1, sizeof(ast_node_variable));
    ast->tok = tok;
    ast->definition = definition;
    ast->base.type = AST_TYPE_VARIABLE;

    return ast;
}
