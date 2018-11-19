#include <stdlib.h>
#include "includes/ast_node_while.h"


ast_node_while* init_ast_node_while(token* tok, ast_node* expr, ast_node_compound* body) {
    ast_node_while* ast;
    ast = calloc(1, sizeof(ast_node_while));
    ast->tok = tok;
    ast->expr = expr;
    ast->body = body;
    ast->base.type = AST_TYPE_WHILE;

    return ast;
}
