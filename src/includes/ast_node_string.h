#ifndef AST_NODE_STRING
#define AST_NODE_STRING
#include "ast_node.h"
typedef struct AST_STRING_STRUCT {
    ast_node base;

    token* tok;
    char* value;
} ast_node_string;


ast_node_string* init_ast_node_string(token* tok, char* value);
#endif
