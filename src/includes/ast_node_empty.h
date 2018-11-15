#ifndef AST_NODE_EMPTY
#define AST_NODE_EMPTY
#include "ast_node.h"
typedef struct AST_EMPTY_STRUCT {
    ast_node base;

    token* tok;
} ast_node_empty;


ast_node_empty* init_ast_node_empty(token* tok);
#endif
