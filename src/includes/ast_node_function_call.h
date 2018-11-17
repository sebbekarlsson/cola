#ifndef AST_NODE_FUNCTION_CALL
#define AST_NODE_FUNCTION_CALL
#include "ast_node.h"
#include "ss_vector.h"
typedef struct AST_FUNCTION_CALL_STRUCT {
    ast_node base;

    token* tok;
    ss_vector* args;
} ast_node_function_call;


ast_node_function_call* init_ast_node_function_call(token* tok, ss_vector* args);
#endif
