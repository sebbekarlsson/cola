#ifndef COLA_AST_NODE_H
#define COLA_AST_NODE_H
#include "token.h"

struct scope;

typedef struct AST_NODE_STRUCT {
    enum {
        AST_TYPE_EMPTY,
        AST_TYPE_BINOP,
        AST_TYPE_UNARYOP,
        AST_TYPE_INTEGER,
        AST_TYPE_FLOAT,
        AST_TYPE_STRING,
        AST_TYPE_CHAR,
        AST_TYPE_COMPOUND,
        AST_TYPE_COMPONENT,
        AST_TYPE_VARIABLE,
        AST_TYPE_FUNCTION_CALL,
        AST_TYPE_VARIABLE_DEFINITION,
        AST_TYPE_FUNCTION_DEFINITION,
        AST_TYPE_IF,
        AST_TYPE_ELSE,
        AST_TYPE_ASSIGN,
        AST_TYPE_WHILE,
        AST_TYPE_FOREACH,
        AST_TYPE_RETURN,
        AST_TYPE_VECPTR
    } type;
    token* tok;
    struct scope* sc;
} ast_node;


ast_node* init_ast_node(token* tok);
struct scope* ast_node_get_scope(ast_node* node);
void ast_node_set_scope(ast_node* node, struct scope* sc);
#endif
