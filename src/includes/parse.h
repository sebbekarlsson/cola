#ifndef COLA_PARSE_H
#define COLA_PARSE_H
#include "lex.h"
#include "scope.h"
#include "ast_node.h"
#include "ast_node_if.h"
#include "ast_node_else.h"
#include "ast_node_while.h"
#include "ast_node_return.h"
#include "ast_node_assign.h"
#include "ast_node_compound.h"
#include "ast_node_component.h"
#include "ast_node_variable.h"
#include "ast_node_integer.h"
#include "ast_node_float.h"
#include "ast_node_vecptr.h"
#include "ast_node_function_call.h"
#include "ast_node_variable_definition.h"
#include "ast_node_function_definition.h"


typedef struct PARSE_STATE_STRUCT {
    lex_state* lex;
    token* current_token;
    int pos;
} parse_state;


parse_state* parse_init();

void parse_eat(parse_state* state, int token_type);

ast_node_integer* parse_integer(parse_state* state, scope* sc);

ast_node_float* parse_float(parse_state* state, scope* sc);

ast_node_vecptr* parse_vecptr(parse_state* state, scope* sc);

ast_node_return* parse_return(parse_state* state, scope* sc);

ast_node_if* parse_if(parse_state* state, scope* sc);

ast_node_else* parse_else(parse_state* state, scope* sc);

ast_node_while* parse_while(parse_state* state, scope* sc);

ast_node_variable* parse_variable(parse_state* state, scope* sc);

ast_node_function_call* parse_function_call(parse_state* state, scope* sc);

ast_node* parse_factor(parse_state* state, scope *sc);

ast_node* parse_term(parse_state* state, scope* sc);

ast_node* parse_expr(parse_state* state, scope* sc);

ss_vector* parse_statement_list(parse_state* state, scope* sc);

ast_node* parse_statement(parse_state* state, scope* sc);

ast_node* parse_any_statement(parse_state* state, scope* sc);

ast_node_compound* parse_compound(parse_state* state, scope* sc);

ast_node_component* parse_component(parse_state* state, scope* sc);

ast_node_compound* parse_parse(parse_state* state, scope* sc);

ast_node_variable_definition* parse_variable_definition(parse_state* state, scope* sc);

ast_node_function_definition* parse_function_definition(parse_state* state, scope* sc);

#endif
