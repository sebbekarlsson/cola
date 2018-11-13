#include "includes/parse.h"
#include "includes/token.h"
#include "includes/ast_node_binop.h"
#include "includes/ast_node_unaryop.h"
#include "includes/ast_node_number.h"
#include <stdlib.h>
#include <stdio.h>


parse_state* parse_init(lex_state* lex) {
    parse_state* state;
    state = malloc(sizeof(struct PARSE_STATE_STRUCT));
    state->lex = lex;
    state->current_token = lex_get_next_token(state->lex);

    return state;
};

void parse_eat(parse_state* state, int token_type) {
    if (state->current_token->type == token_type) {
        state->current_token = lex_get_next_token(state->lex);
    } else {
        printf("Unexpected token_type: `%d`", token_type);
        // TODO: error
    }
};

ast_node* parse_variable(parse_state* state) {
    return (ast_node*) init_ast_node_number(init_token(_TYPE_NUMBER, "1"));
};

ast_node* parse_factor(parse_state* state) {
    token* tok = state->current_token;

    if (tok->type == _OP_PLUS) {
        parse_eat(state, _OP_PLUS);
        ast_node_unaryop* node = init_ast_node_unaryop(tok, parse_factor(state));
        // invalid pointer type
        return (ast_node*) node;

    } else if (tok->type == _OP_SUBTRACT) {
        parse_eat(state, _OP_SUBTRACT);
        ast_node_unaryop* node = init_ast_node_unaryop(tok, parse_factor(state));
        // invalid pointer type
        return (ast_node*) node;

    } else if (tok->type == _NOT_EQUALS) {
        parse_eat(state, _NOT_EQUALS);
        ast_node_unaryop* node = init_ast_node_unaryop(tok, parse_factor(state));
        // invalid pointer type
        return (ast_node*) node;

    } else if (tok->type == _TYPE_NUMBER) {
        parse_eat(state, _TYPE_NUMBER);
        ast_node_number* node = init_ast_node_number(tok);
        // invalid pointer type
        return (ast_node*) node;

    } else {
        printf("Unexpected token_type: `%d`\n", tok->type);
        return (void*)0;
    }

    return (ast_node*) parse_expr(state);
}

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
        node = (ast_node*) init_ast_node_binop(tok, node, parse_factor(state));
    }

    return (ast_node*) node;
}

ast_node* parse_expr(parse_state* state) {
    token* tok = (void*)0;

    // invalid pointer type
    ast_node* node = parse_term(state);

    while(
            state->current_token->type == _OP_PLUS ||
            state->current_token->type == _OP_SUBTRACT ||
            state->current_token->type == _NOT_EQUALS ||
            state->current_token->type == _LESS_THAN ||
            state->current_token->type == _LARGER_THAN ||
            state->current_token->type == _LESS_OR_EQUALS ||
            state->current_token->type == _LARGER_OR_EQUALS ||
            state->current_token->type == _EQUALS ||
            state->current_token->type == _DOT
         ) {
        tok = state->current_token;

        if (tok->type == _OP_PLUS) {
            parse_eat(state, _OP_PLUS);
        } else if (tok->type == _OP_SUBTRACT) {
            parse_eat(state, _OP_SUBTRACT);
        } else if (tok->type == _NOT_EQUALS) {
            parse_eat(state, _NOT_EQUALS);
        } else if (tok->type == _LESS_THAN) {
            parse_eat(state, _LESS_THAN);
        } else if (tok->type == _LARGER_THAN) {
            parse_eat(state, _LARGER_THAN);
        } else if (tok->type == _LESS_OR_EQUALS) {
            parse_eat(state, _LESS_OR_EQUALS);
        } else if (tok->type == _LARGER_OR_EQUALS) {
            parse_eat(state, _LARGER_OR_EQUALS);
        } else if (tok->type == _EQUALS) {
            parse_eat(state, _EQUALS);
        } else if (tok->type == _DOT) {
            parse_eat(state, _DOT);
        }

        // invalid pointer type
        node = (ast_node*) init_ast_node_binop(tok, node, parse_term(state));
    };

    return node;
}

ast_node* parse_statement(parse_state* state) {
    // we only know about expressions as of now
    return parse_expr(state);
};

ast_array* parse_statement_list(parse_state* state) {
    ast_array* nodes = init_ast_array();

    ast_array_append(nodes, parse_statement(state));

    while (state->current_token->type == _SEMI) {
        parse_eat(state, _SEMI);
        ast_array_append(nodes, parse_statement(state));
    }

    return nodes;
};

ast_node_compound* parse_compound(parse_state* state) {
    return init_ast_node_compound(
        (void*)0, parse_statement_list(state)
    );
};

ast_node_compound* parse_parse(parse_state* state) {
    return parse_compound(state);
}
