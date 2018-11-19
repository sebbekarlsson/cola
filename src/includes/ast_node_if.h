#ifndef AST_NODE_IF
#define AST_NODE_IF
#include "ast_node.h"
#include "ast_node_else.h"
#include "ast_node_compound.h"
typedef struct AST_IF_STRUCT {
    ast_node base;

    token* tok;

    ast_node* expr;
    ast_node_compound* body;
    ast_node_else* elsenode;
} ast_node_if;


ast_node_if* init_ast_node_if(token* tok, ast_node* expr, ast_node_compound* body, ast_node_else* elsenode);
#endif
