#include <stdlib.h>
#include "includes/ast_node_function_call.h"


ast_node_function_call* init_ast_node_function_call(token* tok, ss_vector* args) {
    ast_node_function_call* ast;
    ast = calloc(1, sizeof(ast_node_function_call));
    ast->tok = tok;
    ast->args = args;
    ast->base.type = AST_TYPE_FUNCTION_CALL;

    return ast;
}
