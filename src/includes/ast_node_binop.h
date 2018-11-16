#ifndef AST_NODE_BINOP
#define AST_NODE_BINOP
#include "ast_node.h"
typedef struct AST_BINOP_STRUCT {
    ast_node base;

    token* tok;

    char* value;

    ast_node* left;
    ast_node* right;
} ast_node_binop;


ast_node_binop* init_ast_node_binop(token* tok, ast_node* left, ast_node* right);
#endif
