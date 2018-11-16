#include <stdlib.h>
#include "includes/ast_node_char.h"


ast_node_char* init_ast_node_char(token* tok) {
    ast_node_char* ast;
    ast = calloc(1, sizeof(ast_node_char));
    ast->tok = tok;
    ast->base.type = AST_TYPE_CHAR;

    return ast;
}
