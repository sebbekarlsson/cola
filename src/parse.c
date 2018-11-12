#include "includes/parse.h"
#include "includes/token.h"
#include "includes/ast_node_binop.h"
#include <stdlib.h>


parse_state* parse_init(lex_state* lex) {
    parse_state* state;
    state = malloc(sizeof(struct LEX_STATE_STRUCT));
    state->lex = lex;
    state->current_token = lex_get_next_token(state->lex);

    return state;
};

void parse_eat(parse_state* state, int token_type) {};

ast_node* parse_factor(parse_state* state) { return (void*)0; }

ast_node* parse_term(parse_state* state) {
    token* tok = (void*)0;

    ast_node* node = parse_factor(state);
    
    while (
        state->current_token->type == _OP_MULTIPLY ||
        state->current_token->type == _OP_DIVIDE
    ) {
        tok = state->current_token;

        if (tok->type == _OP_MULTIPLY) {
            parse_eat(state, _OP_MULTIPLY);
        } else if (tok->type == _OP_DIVIDE) {
            parse_eat(state, _OP_DIVIDE);
        }

        // this probably wont work since `node` is of pointer type ast_node*
        node = init_ast_node_binop(tok, node, parse_factor(state));
    }

    return node;
}

ast_node* parse_expr(parse_state* state) { return (void*)0; }

ast_node* parse_parse() { return (void*)0; }
