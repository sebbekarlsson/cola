#include <stdlib.h>
#include "includes/ast_node_binop.h"


ast_node_binop* init_ast_node_binop(token* tok, ast_node* left, ast_node* right) {
    ast_node_binop* ast;
    ast = malloc(sizeof(ast_node_binop));
    ast->tok = tok;
    ast->left = left;
    ast->right = right;

    return ast;
}
