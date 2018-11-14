#ifndef AST_NODE_VARIABLE
#define AST_NODE_VARIABLE
#include "ast_node.h"
#include "ast_node_variable_definition.h"
typedef struct AST_VARIABLE_STRUCT {
    ast_node base;

    token* tok;

    ast_node_variable_definition* definition;
} ast_node_variable;


ast_node_variable* init_ast_node_variable(token* tok, ast_node_variable_definition* definition);
#endif
