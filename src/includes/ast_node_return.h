#ifndef AST_NODE_RETURN
#define AST_NODE_RETURN
#include "ast_node.h"
typedef struct AST_RETURN_STRUCT {
    ast_node base;

    token* tok;
    ast_node* value;
} ast_node_return;


ast_node_return* init_ast_node_return(token* tok, ast_node* value);
#endif
