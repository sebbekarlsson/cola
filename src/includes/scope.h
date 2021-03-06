#ifndef COLA_SCOPE_H
#define COLA_SCOPE_H
#include "token.h"
#include "ss_vector.h"
#include "ast_node_variable_definition.h"
#include "ast_node_function_definition.h"
#include "ast_node_component.h"


typedef struct SCOPE_STRUCT {
    ss_vector* variables;
    ss_vector* functions;
    ss_vector* components;
} scope;


scope* init_scope();

void save_variable_definition(scope* sc, ast_node_variable_definition* node);
void delete_variable_definition(scope* sc, char* name);
void save_function_definition(scope* sc, ast_node_function_definition* node);
void save_component(scope* sc, ast_node_component* node);

ast_node_variable_definition* get_variable_definition(scope* sc, char* name);
ast_node_function_definition* get_function_definition(scope* sc, char* name);
ast_node_component* get_component(scope* sc, char* name);
#endif
