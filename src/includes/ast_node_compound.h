#ifndef AST_NODE_COMPUND
#define AST_NODE_COMPUND
#include "ast_node.h"
#include "Vector.h"
typedef struct AST_COMPUND_STRUCT {
    ast_node base;

    token* tok;

    Vector nodes;
} ast_node_compound;


ast_node_compound* init_ast_node_compound(token* tok, Vector nodes);
#endif
