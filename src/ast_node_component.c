#include <stdlib.h>
#include "includes/ast_node_component.h"


ast_node_component* init_ast_node_component(token* tok, token* name, ast_node_compound* body, ss_vector* deps) {
    ast_node_component* ast;
    ast = calloc(1, sizeof(ast_node_component));
    ast->tok = tok;
    ast->name = name;
    ast->body = body;
    ast->deps = deps;
    ast->base.type = AST_TYPE_COMPONENT;

    return ast;
}
