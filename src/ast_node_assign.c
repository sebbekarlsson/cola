#include <stdlib.h>
#include "includes/ast_node_assign.h"


ast_node_assign* init_ast_node_assign(token* tok, ast_node* left, ast_node* right) {
    ast_node_assign* ast;
    ast = calloc(1, sizeof(ast_node_assign));
    ast->tok = tok;
    ast->left = left;
    ast->right = right;
    ast->base.type = AST_TYPE_ASSIGN;

    return ast;
}
