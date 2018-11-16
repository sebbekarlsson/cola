#include <stdlib.h>
#include "includes/ast_node_compound.h"


ast_node_compound* init_ast_node_compound(token* tok, ast_array* nodes) {
    ast_node_compound* ast;
    ast = calloc(1, sizeof(ast_node_compound));
    ast->tok = tok;
    ast->nodes = nodes;
    ast->base.type = AST_TYPE_COMPOUND;

    return ast;
}
