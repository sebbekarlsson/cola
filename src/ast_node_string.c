#include <stdlib.h>
#include "includes/ast_node_string.h"


ast_node_string* init_ast_node_string(token* tok, char* value) {
    ast_node_string* ast;
    ast = calloc(1, sizeof(ast_node_string));
    ast->tok = tok;
    ast->value = value;
    ast->base.type = AST_TYPE_STRING;

    return ast;
}
