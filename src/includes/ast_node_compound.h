#ifndef AST_NODE_COMPUND
#define AST_NODE_COMPUND
#include "ast_node.h"
#include "ss_vector.h"
typedef struct AST_COMPUND_STRUCT {
    ast_node base;

    token* tok;

    ss_vector* nodes;
} ast_node_compound;


ast_node_compound* init_ast_node_compound(token* tok, ss_vector* nodes);
#endif
