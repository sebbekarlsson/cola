#include "includes/default_scope_initialize.h"
#include "includes/scope.h"
#include "includes/ast_node_integer.h"
#include "includes/ast_node_empty.h"
#include <stdio.h>

ast_node* print(ast_array* args) {
    for (int i = 0; i < args->size; i++) {
        ast_node* node = ast_array_get(args, i);

        if (node->type == AST_TYPE_INTEGER) {
            ast_node_integer* node_integer = (ast_node_integer*) node;
            printf("%s\n", node_integer->tok->value);
        }
    }

    return (ast_node*) init_ast_node_empty((void*)0);
};

void default_scope_initialize(scope* sc) {

    ast_array* args = init_ast_array();

    ast_node_function_definition* definition = init_ast_node_function_definition(
        init_token(_ID, "print"),
        _DATA_TYPE_VOID,
        args,
        (void*)0
    );

    definition->call = print;

    save_function_definition(sc, definition);
}
