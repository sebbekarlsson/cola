#ifndef AST_NODE_CHAR
#define AST_NODE_CHAR
#include "ast_node.h"
typedef struct AST_CHAR_STRUCT {
    ast_node base;

    token* tok;
    char value;
} ast_node_char;


ast_node_char* init_ast_node_char(token* tok, char value);
#endif
