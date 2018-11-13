#ifndef AST_NODE_VARIABLE_DEFINITION
#define AST_NODE_VARIABLE_DEFINITION
#include "ast_node.h"
typedef struct AST_VARIABLE_DEFINITION_STRUCT {
    ast_node base;

    token* tok;
    
    int data_type;
    ast_node* value;
} ast_node_variable_definition;


ast_node_variable_definition* init_ast_node_variable_definition(token* tok, int data_type, ast_node* value);
#endif
