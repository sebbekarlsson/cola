#ifndef AST_NODE_INTEGER
#define AST_NODE_INTEGER
#include "ast_node.h"
typedef struct AST_INTEGER_STRUCT {
    ast_node base;

    token* tok;
    int value;
} ast_node_integer;


ast_node_integer* init_ast_node_integer(token* tok, int value);
#endif
