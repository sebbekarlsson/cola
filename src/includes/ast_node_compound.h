#ifndef AST_NODE_COMPUND
#define AST_NODE_COMPUND
#include "ast_node.h"
#include "ast_array.h"
typedef struct AST_COMPUND_STRUCT {
    ast_node base;

    token* tok;

    ast_array* nodes;
} ast_node_compound;


ast_node_compound* init_ast_node_compound(token* tok, ast_array* nodes);
#endif
