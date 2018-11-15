#include "includes/lex.h"
#include "includes/strutils.h"
#include "includes/parse_id.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>


lex_state* lex_init(char* buffer) {
    lex_state* state;
    state = malloc(sizeof(struct LEX_STATE_STRUCT));
    state->buffer = buffer;
    state->pos = 0;
    state->current_char = state->buffer[state->pos];

    return state;
};

/**
 * Moves the cursor / position to the next position.
 *
 * @param lex_state* state
 */
void lex_advance(lex_state* state) {
    if (state->buffer[state->pos] != '\0') {
        state->pos += 1;
        state->current_char = state->buffer[state->pos];
    }
};

/**
 * Get the next token based on the position and the buffer
 *
 * @param lex_state* state
 */
token* lex_get_next_token(lex_state* state) {
    while (state->current_char != '\0') {
        char* str = char_to_string(state->current_char); 

        if (state->current_char == ' ' || (int)state->current_char == 10 || state->current_char == '\0') {
            lex_skip_whitespace(state);
            free(str);
            continue;
        }

        else if (state->current_char == '+') {
            lex_advance(state);
            return init_token(_OP_PLUS, str);
        }

        else if (state->current_char == '-') {
            lex_advance(state);
            return init_token(_OP_SUBTRACT, str);
        }

        else if (state->current_char == '/') {
            lex_advance(state);
            return init_token(_OP_DIVIDE, str);
        }

        else if (state->current_char == '*') {
            lex_advance(state);
            return init_token(_OP_MULTIPLY, str);
        }

        else if (state->current_char == '(') {
            lex_advance(state);
            return init_token(_LPAREN, str);
        }

        else if (state->current_char == ')') {
            lex_advance(state);
            return init_token(_RPAREN, str);
        }

        else if (state->current_char == '{') {
            lex_advance(state);
            return init_token(_LBRACE, str);
        }

        else if (state->current_char == '}') {
            lex_advance(state);
            return init_token(_RBRACE, str);
        }

        else if (state->current_char == ';') {
            lex_advance(state);
            return init_token(_SEMI, str);
        }

        else if (state->current_char == '.') {
            lex_advance(state);
            return init_token(_DOT, str);
        }

        else if (state->current_char == ',') {
            lex_advance(state);
            return init_token(_COMMA, str);
        }

        else if (state->current_char == '@') {
            lex_advance(state);
            return init_token(_AT, str);
        }

        else if (state->current_char == '<') {
            lex_advance(state);
            return init_token(_LESS_THAN, str);
        }
        
        else if (state->current_char == '>') {
            lex_advance(state);
            return init_token(_LARGER_THAN, str);
        }

        else if (state->current_char == '=') {
            lex_advance(state);
            return init_token(_EQUALS, str);
        }

        else if (state->current_char == '"') {
            free(str);
            return init_token(_STRING, lex_parse_string(state));
        }

        else if (isdigit(state->current_char)) {
            free(str);
            return init_token(_TYPE_NUMBER, lex_parse_number(state));
        }

        else if (isalnum(state->current_char)) {
            free(str);
            return parse_id(state, init_token(_ID, lex_parse_id(state)));
        } else {
            printf("Unexpected token: `%s` (%d) \n", str, (int) state->current_char);
            break;
        }

        free(str);
        lex_advance(state);
    }

    return init_token(_EOF, "");
};

/**
 * Used to skip white space until we get to a interesting char.
 *
 * @param lex_state* state
 */
void lex_skip_whitespace(lex_state* state) {
    lex_advance(state);

    while ((state->current_char == ' ' ||  (int) state->current_char == 10) && state->current_char != '\0')
        lex_advance(state);
};

char lex_peek_next(lex_state* state, int start) {
    int peek_pos = start;
    char c = '\0';

    while (peek_pos < (int)strlen(state->buffer)) {
        c = state->buffer[peek_pos];

        if (c == '\0' || c == ' ' || c == '\n') {
            peek_pos++;
            continue;
        } else {
            break;
        }
    }

    return c;
}

/**
 * Parses an ID, this is quite vague but it is chunks of string which is
 * alpha numerical.
 *
 * @param lex_state* state
 */
char* lex_parse_id(lex_state* state) {
    char* buff;
    char* charstr;

    buff = calloc(2, sizeof(char*));
    charstr = char_to_string(state->current_char);
    strcat(buff, charstr);
    lex_advance(state);
    free(charstr);

    while (isalnum(state->current_char) || state->current_char == '_') {
        buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
        charstr = char_to_string(state->current_char);
        strcat(buff, charstr);
        lex_advance(state);
        free(charstr);
    }

    return buff;
};

/**
 * Parses a number, basically a piece of string which is completely
 * numerical
 *
 * @param lex_state* state
 */
char* lex_parse_number(lex_state* state) {
    char* buff;
    char* charstr;

    buff = calloc(2, sizeof(char*));
    charstr = char_to_string(state->current_char);
    strcat(buff, charstr);
    lex_advance(state);
    free(charstr);

    while (isdigit(state->current_char)) {
        buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
        charstr = char_to_string(state->current_char);
        strcat(buff, charstr);
        lex_advance(state);
        free(charstr);
    }

    // float
    if (state->current_char == '.') {
        buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
        charstr = char_to_string(state->current_char);
        strcat(buff, charstr);
        lex_advance(state);

        while (isdigit(state->current_char)) {
            buff = realloc(buff, sizeof(buff) + (sizeof(char) * 2));
            charstr = char_to_string(state->current_char);
            strcat(buff, charstr);
            lex_advance(state);
        }

        free(charstr);
    }

    return buff;
}

/**
 * Capture everything between `"`
 *
 * @param lex_state*
 *
 * @return char*
 */
char* lex_parse_string(lex_state* state) {
    lex_advance(state);

    char* buff;
    char* charstr;

    buff = calloc(2, sizeof(char*));
    charstr = char_to_string(state->current_char);
    strcat(buff, charstr);
    lex_advance(state);
    free(charstr);

    while (state->current_char != '\0') {
        if (state->current_char == '"')
            break;

        buff = realloc(buff, strlen(buff) + (sizeof(char) * 2));
        charstr = char_to_string(state->current_char);
        strcat(buff, charstr);
        lex_advance(state);
        free(charstr);
    }

    lex_advance(state);

    return buff;
}
