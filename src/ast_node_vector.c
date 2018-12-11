#include <stdlib.h>
#include "includes/ast_node_vector.h"


ast_node_vector* init_ast_node_vector(token* tok, int data_type, ss_vector* vector) {
    ast_node_vector* ast;
    ast = calloc(1, sizeof(ast_node_vector));
    ast->tok = tok;
    ast->data_type = data_type;
    ast->vector = vector;
    ast->base.type = AST_TYPE_VECTOR;

    return ast;
}
