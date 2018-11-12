#include "includes/parse.h"
#include "includes/token.h"
#include <stdlib.h>


parse_state* parse_init(lex_state* lex) {
    parse_state* state;
    state = malloc(sizeof(struct LEX_STATE_STRUCT));
    state->lex = lex;
    state->current_token = lex_get_next_token(state->lex);

    return state;
};

ast_node* parse_factor(parse_state* state) { return (void*)0; }

ast_node* parse_term(parse_state* state) { return (void*)0; }

ast_node* parse_expr(parse_state* state) { return (void*)0; }

ast_node* parse_parse() { return (void*)0; }
