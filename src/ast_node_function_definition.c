#include <stdlib.h>
#include "includes/ast_node_function_definition.h"



ast_node_function_definition* init_ast_node_function_definition(
    token* tok,
    int data_type,
    ss_vector* args,
    ast_node_compound* body
) {
    ast_node_function_definition* ast;
    ast = calloc(1, sizeof(ast_node_function_definition));
    ast->tok = tok;
    ast->data_type = data_type;
    ast->args = args;
    ast->body = body;
    ast->base.type = AST_TYPE_FUNCTION_DEFINITION;

    return ast;
}
