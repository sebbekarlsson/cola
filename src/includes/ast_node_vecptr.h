#ifndef AST_NODE_VECPTR
#define AST_NODE_VECPTR
#include "ast_node.h"
typedef struct AST_VECPTR_STRUCT {
    ast_node base;

    token* tok;
    ast_node* target;
    ast_node* index;
} ast_node_vecptr;


ast_node_vecptr* init_ast_node_vecptr(token* tok, ast_node* target, ast_node* index);
#endif
