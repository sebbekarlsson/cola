#ifndef COLA_AST_NODE_H
#define COLA_AST_NODE_H
#include "token.h"


typedef struct AST_NODE_STRUCT {
    token* tok;
} ast_node;


ast_node* init_ast_node(token* tok);
#endif
