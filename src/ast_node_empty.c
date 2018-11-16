#include <stdlib.h>
#include "includes/ast_node_empty.h"


ast_node_empty* init_ast_node_empty(token* tok) {
    ast_node_empty* ast;
    ast = calloc(1, sizeof(ast_node_empty));
    ast->tok = tok;
    ast->base.type = AST_TYPE_EMPTY;

    return ast;
}
