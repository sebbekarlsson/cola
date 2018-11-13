#include <stdlib.h>
#include "includes/ast_node_compound.h"


ast_node_compound* init_ast_node_compound(token* tok, Vector nodes) {
    ast_node_compound* ast;
    ast = malloc(sizeof(ast_node_compound));
    ast->tok = tok;
    ast->nodes = nodes;
    ast->base.type = AST_TYPE_COMPOUND;

    return ast;
}
