#include <stdlib.h>
#include "includes/ast_node_foreach.h"


ast_node_foreach* init_ast_node_foreach(
    token* tok,
    ast_node* iterable,
    token* value_name,
    ast_node_compound* body
) {
    ast_node_foreach* ast;
    ast = calloc(1, sizeof(ast_node_foreach));
    ast->tok = tok;
    ast->iterable = iterable;
    ast->value_name = value_name;
    ast->body = body;
    ast->base.type = AST_TYPE_FOREACH;

    return ast;
}
