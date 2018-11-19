#ifndef AST_NODE_WHILE
#define AST_NODE_WHILE
#include "ast_node.h"
#include "ast_node_compound.h"
typedef struct AST_WHILE_STRUCT {
    ast_node base;

    token* tok;

    ast_node* expr;
    ast_node_compound* body;
} ast_node_while;


ast_node_while* init_ast_node_while(token* tok, ast_node* expr, ast_node_compound* body);
#endif
