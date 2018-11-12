#ifndef AST_NODE_NUMBER
#define AST_NODE_NUMBER
#include "ast_node.h"
typedef struct AST_NUMBER_STRUCT {
    ast_node base;

    token* tok;

    ast_node* right;
} ast_node_number;


ast_node_number* init_ast_node_number(token* tok);
#endif
