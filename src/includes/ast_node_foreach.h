#ifndef AST_NODE_FOREACH
#define AST_NODE_FOREACH
#include "ast_node.h"
#include "ast_node_compound.h"
typedef struct AST_FOREACH_STRUCT {
    ast_node base;

    token* tok;

    ast_node* iterable;
    token* value_name;
    ast_node_compound* body;
} ast_node_foreach;


ast_node_foreach* init_ast_node_foreach(
    token* tok,
    ast_node* iterable,
    token* value_name,
    ast_node_compound* body
);
#endif
