#include <stdlib.h>
#include "includes/ast_node_integer.h"


ast_node_integer* init_ast_node_integer(token* tok) {
    ast_node_integer* ast;
    ast = malloc(sizeof(ast_node_integer));
    ast->tok = tok;
    ast->base.type = AST_TYPE_INTEGER;

    return ast;
}
