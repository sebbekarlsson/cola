#ifndef AST_NODE_FLOAT
#define AST_NODE_FLOAT
#include "ast_node.h"
typedef struct AST_FLOAT_STRUCT {
    ast_node base;

    token* tok;
    float value;
} ast_node_float;


ast_node_float* init_ast_node_float(token* tok, float value);
#endif
