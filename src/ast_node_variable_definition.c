#include <stdlib.h>
#include "includes/ast_node_variable_definition.h"


ast_node_variable_definition* init_ast_node_variable_definition(token* tok, int data_type, ast_node* value) {
    ast_node_variable_definition* ast;
    ast = malloc(sizeof(ast_node_variable_definition));
    ast->tok = tok;
    ast->data_type = data_type;
    ast->value = value;
    ast->base.type = AST_TYPE_VARIABLE_DEFINITION;

    return ast;
}
