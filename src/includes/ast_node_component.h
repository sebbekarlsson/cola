#ifndef AST_NODE_COMPONENT
#define AST_NODE_COMPONENT
#include "ast_node.h"
#include "ast_node_compound.h"
typedef struct AST_COMPONENT_STRUCT {
    ast_node base;

    token* tok;
    token* name;
    ast_node_compound* body;
    ss_vector* deps;

} ast_node_component;


ast_node_component* init_ast_node_component(token* tok, token* name, ast_node_compound* body, ss_vector* deps);
#endif
