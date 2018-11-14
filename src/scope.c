#include <stdlib.h>
#include "includes/scope.h"


scope* init_scope() {
    scope* sc;
    sc = malloc(sizeof(scope));
    sc->variables = init_ast_array();
    sc->functions = init_ast_array();

    return sc;
}


void save_variable_definition(scope* sc, ast_node_variable_definition* node) {
    ast_array_append(sc->variables, (ast_node*) node);
}

void save_function_definition(scope* sc, ast_node_function_definition* node) {
    ast_array_append(sc->functions, (ast_node*) node);
}


ast_node_variable_definition* get_variable_definition(scope* sc, char* name) {
    ast_node_variable_definition* definition;

    for (int i = 0; i < sc->variables->size; i++) {
        definition = (ast_node_variable_definition*) ast_array_get(sc->variables, i);

        if (strcmp(definition->tok->value, name) == 0) {
            break;
        } else {
            definition = (void*)0;
        }
    }

    return definition;
}
