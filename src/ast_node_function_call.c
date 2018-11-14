#include <stdlib.h>
#include "includes/ast_node_function_call.h"


ast_node_function_call* init_ast_node_function_call(token* tok, ast_array* args) {
    ast_node_function_call* ast;
    ast = malloc(sizeof(ast_node_function_call));
    ast->tok = tok;
    ast->args = args;
    ast->base.type = AST_TYPE_FUNCTION_CALL;

    return ast;
}
