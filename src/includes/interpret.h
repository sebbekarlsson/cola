#ifndef INTERPRET_INTERPRET_H
#define INTERPRET_INTERPRET_H
#include "token.h"
#include "ast_node.h"
#include "ast_node_compound.h"
#include "ast_node_binop.h"
#include "ast_node_empty.h"
#include "ast_node_number.h"
#include "ast_node_integer.h"
#include "ast_node_component.h"
#include "ast_node_variable.h"
#include "ast_node_function_call.h"
#include "ast_node_variable_definition.h"
#include "ast_node_function_definition.h"


/*typedef struct INTERPRET_STATE_STRUCT {
    char* buffer;
    char current_char;
    int pos;
} interpret_state;


interpret_state* interpret_init();*/

ast_node* interpret_visit(ast_node* node);
ast_node* interpret_visit_empty(ast_node_empty* node);
ast_node* interpret_visit_compound(ast_node_compound* node);
ast_node* interpret_visit_binop(ast_node_binop* node);
ast_node* interpret_visit_number(ast_node_number* node);
ast_node* interpret_visit_integer(ast_node_integer* node);
ast_node* interpret_visit_component(ast_node_component* node);
ast_node* interpret_visit_variable(ast_node_variable* node);
ast_node* interpret_visit_function_call(ast_node_function_call* node);
ast_node* interpret_visit_variable_definition(ast_node_variable_definition* node);
ast_node* interpret_visit_function_definition(ast_node_function_definition* node);

#endif
