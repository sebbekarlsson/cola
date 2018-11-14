#ifndef LEX_LEX_H
#define LEX_LEX_H
#include "token.h"


typedef struct LEX_STATE_STRUCT {
    char* buffer;
    char current_char;
    int pos;
} lex_state;


lex_state* lex_init();

token* lex_get_next_token(lex_state* state);

void lex_skip_whitespace(lex_state* state);

char lex_peek_next(lex_state* state, int start);

char* lex_parse_id(lex_state* state);

char* lex_parse_number(lex_state* state);

char* lex_parse_string(lex_state* state);

#endif
