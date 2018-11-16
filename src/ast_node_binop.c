#include <stdlib.h>
#include "includes/ast_node_binop.h"


ast_node_binop* init_ast_node_binop(token* tok, ast_node* left, ast_node* right) {
    ast_node_binop* ast;
    ast = calloc(1, sizeof(ast_node_binop));
    ast->tok = tok;
    ast->value = malloc(sizeof(char*));
    ast->left = left;
    ast->right = right;
    ast->base.type = AST_TYPE_BINOP;

    return ast;
}
