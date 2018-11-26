#include "includes/default_scope_initialize.h"
#include "includes/scope.h"
#include "includes/ast_node_integer.h"
#include "includes/ast_node_float.h"
#include "includes/ast_node_empty.h"
#include "includes/ast_node_char.h"
#include <stdio.h>

ast_node* print(ss_vector* args) {
    for (int i = 0; i < args->size; i++) {
        ast_node* node = (ast_node*)args->items[i];

        if (node->type == AST_TYPE_INTEGER) {
            ast_node_integer* node_integer = (ast_node_integer*) node;
            printf("%d\n", node_integer->value);
        } else if (node->type == AST_TYPE_FLOAT) {
            ast_node_float* node_float = (ast_node_float*) node;
            printf("%f\n", node_float->value);
        } else if (node->type == AST_TYPE_CHAR) {
            ast_node_char* node_char = (ast_node_char*) node;
            printf("%c\n", node_char->value);
        } else {
            printf("<%d>\n", (int)node->type);
        }
    }

    return (ast_node*) init_ast_node_empty((void*)0);
};

void default_scope_initialize(scope* sc) {

    ss_vector* args = ss_init_vector(sizeof(ast_node));

    ast_node_function_definition* definition = init_ast_node_function_definition(
        init_token(_ID, "print"),
        _DATA_TYPE_VOID,
        args,
        (void*)0
    );

    definition->call = print;

    save_function_definition(sc, definition);
}
