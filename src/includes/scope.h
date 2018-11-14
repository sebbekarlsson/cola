#ifndef COLA_SCOPE_H
#define COLA_SCOPE_H
#include "token.h"
#include "ast_array.h"
#include "ast_node_variable_definition.h"
#include "ast_node_function_definition.h"


typedef struct SCOPE_STRUCT {
    ast_array* variables;
    ast_array* functions;
} scope;


scope* init_scope();
void save_variable_definition(scope* sc, ast_node_variable_definition* node);
void save_function_definition(scope* sc, ast_node_function_definition* node);
#endif
