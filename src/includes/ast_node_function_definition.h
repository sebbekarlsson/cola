#ifndef AST_NODE_FUNCTION_DEFINITION
#define AST_NODE_FUNCTION_DEFINITION
#include "ast_node.h"
#include "ast_array.h"
#include "ast_node_compound.h"
typedef struct AST_FUNCTION_DEFINITION_STRUCT {
    ast_node base;

    token* tok;
    
    int data_type;
    ast_array* args;
    ast_node_compound* body;
    ast_node* (*call)();
} ast_node_function_definition;


ast_node_function_definition* init_ast_node_function_definition(
    token* tok,
    int data_type,
    ast_array* args,
    ast_node_compound* body
);
#endif
