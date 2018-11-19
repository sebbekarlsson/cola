#include <stdlib.h>
#include "includes/ast_node_if.h"


ast_node_if* init_ast_node_if(token* tok, ast_node* expr, ast_node_compound* body, ast_node_else* elsenode) {
    ast_node_if* ast;
    ast = calloc(1, sizeof(ast_node_if));
    ast->tok = tok;
    ast->expr = expr;
    ast->body = body;
    ast->elsenode = elsenode;
    ast->base.type = AST_TYPE_IF;

    return ast;
}
