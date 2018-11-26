#include <stdlib.h>
#include "includes/ast_node_float.h"


ast_node_float* init_ast_node_float(token* tok, float value) {
    ast_node_float* ast;
    ast = calloc(1, sizeof(ast_node_float));
    ast->tok = tok;
    ast->value = value;
    ast->base.type = AST_TYPE_FLOAT;

    return ast;
}
