#include <stdlib.h>
#include "includes/ast_node_integer.h"


ast_node_integer* init_ast_node_integer(token* tok, int value) {
    ast_node_integer* ast;
    ast = calloc(1, sizeof(ast_node_integer));
    ast->tok = tok;
    ast->value = value;
    ast->base.type = AST_TYPE_INTEGER;

    return ast;
}
