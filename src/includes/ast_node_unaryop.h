#ifndef AST_NODE_UNARYOP
#define AST_NODE_UNARYOP
#include "ast_node.h"
typedef struct AST_UNARYOP_STRUCT {
    ast_node base;

    token* tok;

    ast_node* right;
} ast_node_unaryop;


ast_node_unaryop* init_ast_node_unaryop(token* tok, ast_node* right);
#endif
