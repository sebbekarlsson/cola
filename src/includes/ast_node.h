#ifndef COLA_AST_NODE_H
#define COLA_AST_NODE_H
#include "token.h"


typedef struct AST_NODE_STRUCT {
    enum {
        AST_TYPE_BINOP,
        AST_TYPE_UNARYOP,
        AST_TYPE_NUMBER,
        AST_TYPE_INTEGER,
        AST_TYPE_COMPOUND,
        AST_TYPE_COMPONENT,
        AST_TYPE_VARIABLE_DEFINITION
    } type;
    token* tok;
} ast_node;


ast_node* init_ast_node(token* tok);
#endif
