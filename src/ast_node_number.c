#include <stdlib.h>
#include "includes/ast_node_number.h"


ast_node_number* init_ast_node_number(token* tok) {
    ast_node_number* ast;
    ast = malloc(sizeof(ast_node_number));
    ast->tok = tok;
    ast->base.type = AST_TYPE_NUMBER;

    return ast;
}
