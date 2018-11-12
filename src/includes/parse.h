#ifndef COLA_PARSE_H
#define COLA_PARSE_H
#include "lex.h"
#include "ast_node.h"


typedef struct PARSE_STATE_STRUCT {
    lex_state* lex;
    token* current_token;
    int pos;
} parse_state;


parse_state* parse_init();

void parse_eat(parse_state* state, int token_type);

ast_node* parse_factor(parse_state* state);

ast_node* parse_term(parse_state* state);

ast_node* parse_expr(parse_state* state);

ast_node* parse_any_statement(parse_state* state);

ast_node* parse_parse(parse_state* state);

#endif
