#ifndef AST_NODE_ELSE
#define AST_NODE_ELSE
#include "ast_node.h"
#include "ast_node_compound.h"
#include "ss_vector.h"

struct ast_node_if;

typedef struct AST_ELSE_STRUCT {
    ast_node base;

    token* tok;

    ast_node_compound* body;
    struct ast_node_if* ifnode;
} ast_node_else;


ast_node_else* init_ast_node_else(token* tok, ast_node_compound* body, struct ast_node_if* ifnode);
#endif
