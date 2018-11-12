#include <stdlib.h>
#include "includes/ast_node.h"


ast_node* init_ast_node(token* tok) {
    ast_node* ast;
    ast = malloc(sizeof(ast_node));
    ast->tok = tok;

    return ast;
}
