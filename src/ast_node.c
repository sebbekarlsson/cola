#include <stdlib.h>
#include "includes/ast_node.h"
#include "includes/scope.h"

extern scope* global_scope;

ast_node* init_ast_node(token* tok) {
    ast_node* ast;
    ast = malloc(sizeof(ast_node));
    ast->tok = tok;

    return ast;
}

struct scope* ast_node_get_scope(ast_node* node) {
    return (node->sc ? node->sc : (struct scope*) global_scope);
}
