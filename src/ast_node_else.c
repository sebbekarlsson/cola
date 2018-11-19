#include <stdlib.h>
#include "includes/ast_node_else.h"


ast_node_else* init_ast_node_else(token* tok, ast_node_compound* body, struct ast_node_if* ifnode) {
    ast_node_else* ast;
    ast = calloc(1, sizeof(ast_node_else));
    ast->tok = tok;
    ast->body = body;
    ast->ifnode = ifnode;
    ast->base.type = AST_TYPE_ELSE;

    return ast;
}
