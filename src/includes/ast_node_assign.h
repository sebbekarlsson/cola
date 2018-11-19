#ifndef AST_NODE_VARIABLE_ASSIGN
#define AST_NODE_VARIABLE_ASSIGN
#include "ast_node.h"
typedef struct AST_ASSIGN_STRUCT {
    ast_node base;

    token* tok;
    
    ast_node* left;
    ast_node* right;
} ast_node_assign;


ast_node_assign* init_ast_node_assign(token* tok, ast_node* left, ast_node* right);
#endif
