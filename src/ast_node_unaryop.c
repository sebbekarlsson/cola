#include <stdlib.h>
#include "includes/ast_node_unaryop.h"


ast_node_unaryop* init_ast_node_unaryop(token* tok, ast_node* right) {
    ast_node_unaryop* ast;
    ast = malloc(sizeof(ast_node_unaryop));
    ast->tok = tok;
    ast->right = right;
    ast->base.type = AST_TYPE_UNARYOP;

    return ast;
}
