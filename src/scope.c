#include <stdlib.h>
#include "includes/scope.h"


scope* init_scope() {
    scope* sc;
    sc = malloc(sizeof(scope));
    sc->variables = ss_init_vector(sizeof(ast_node_variable_definition));
    sc->functions = ss_init_vector(sizeof(ast_node_function_definition));
    sc->components = ss_init_vector(sizeof(ast_node_component));

    return sc;
}


void save_variable_definition(scope* sc, ast_node_variable_definition* node) {
    ss_vector_append(sc->variables, (ast_node*) node);
}

void save_function_definition(scope* sc, ast_node_function_definition* node) {
    ss_vector_append(sc->functions, (ast_node*) node);
}

void save_component(scope* sc, ast_node_component* node) {
    ss_vector_append(sc->components, (ast_node_component*) node);
}


ast_node_variable_definition* get_variable_definition(scope* sc, char* name) {
    ast_node_variable_definition* definition = (void*)0;

    for (int i = 0; i < sc->variables->size; i++) {
        definition = (ast_node_variable_definition*) sc->variables->items[i];

        if (strcmp(definition->tok->value, name) == 0) {
            break;
        } else {
            definition = (void*)0;
        }
    }

    return definition;
}


ast_node_function_definition* get_function_definition(scope* sc, char* name) {
    ast_node_function_definition* definition = (void*)0;

    for (int i = 0; i < sc->functions->size; i++) {
        definition = (ast_node_function_definition*) sc->functions->items[i];

        if (definition) {
            if (definition->tok) {
                if (definition->tok->value) {
        if (strcmp(definition->tok->value, name) == 0) {
            break;
        } else {
            definition = (void*)0;
        }
            }
        }
        }
    }

    return definition;
}

ast_node_component* get_component(scope* sc, char* name) {
    ast_node_component* component = (void*)0;

    for (int i = 0; i < sc->components->size; i++) {
        component = (ast_node_component*) sc->components->items[i];

        if (strcmp(component->tok->value, name) == 0) {
            break;
        } else {
            component = (void*)0;
        }
    }

    return component;
}
