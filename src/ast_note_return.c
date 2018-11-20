#include <stdlib.h>
#include "includes/ast_node_return.h"


ast_node_return* init_ast_node_return(token* tok, ast_node* value) {
    ast_node_return* ast;
    ast = calloc(1, sizeof(ast_node_return));
    ast->tok = tok;
    ast->value = value;
    ast->base.type = AST_TYPE_RETURN;

    return ast;
}
