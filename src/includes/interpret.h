#ifndef INTERPRET_INTERPRET_H
#define INTERPRET_INTERPRET_H
#include "token.h"
#include "ast_node.h"
#include "ast_node_if.h"
#include "ast_node_else.h"
#include "ast_node_while.h"
#include "ast_node_return.h"
#include "ast_node_char.h"
#include "ast_node_binop.h"
#include "ast_node_empty.h"
#include "ast_node_number.h"
#include "ast_node_integer.h"
#include "ast_node_compound.h"
#include "ast_node_variable.h"
#include "ast_node_component.h"
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
ast_node* interpret_visit_if(ast_node_if* node);
ast_node* interpret_visit_return(ast_node_return* node);
ast_node* interpret_visit_else(ast_node_else* node);
ast_node* interpret_visit_while(ast_node_while* node);
ast_node* interpret_visit_char(ast_node_char* node);
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
