#include <stdlib.h>
#include "includes/ast_node_vecptr.h"


ast_node_vecptr* init_ast_node_vecptr(token* tok, ast_node* target, ast_node* index) {
    ast_node_vecptr* ast;
    ast = calloc(1, sizeof(ast_node_vecptr));
    ast->tok = tok;
    ast->target = target;
    ast->index = index;
    ast->base.type = AST_TYPE_VECPTR;

    return ast;
}
