#include "includes/parse_id.h"
#include "includes/tokentype.h"


token* parse_id(lex_state* state, token* token) {
    if (
        strcmp(token->value, "string") == 0 ||
        strcmp(token->value, "int") == 0 ||
        strcmp(token->value, "struct") == 0 ||
        strcmp(token->value, "void") == 0 ||
        strcmp(token->value, "float") == 0 ||
        strcmp(token->value, "char") == 0
    ) {
        token->type = _DATA_TYPE;
    } else if (strcmp(token->value, "comp") == 0) {
        token->type = _TYPE_COMPONENT;
    } else if (strcmp(token->value, "use") == 0) {
        token->type = _USE;
    } else if (strcmp(token->value, "if") == 0) {
        token->type = _IF;
    } else if (strcmp(token->value, "else") == 0) {
        token->type = _ELSE;
    } else if (strcmp(token->value, "while") == 0) {
        token->type = _WHILE;
    } else if (strcmp(token->value, "function") == 0) {
        token->type = _TYPE_FUNCTION;
    } else if (lex_peek_next(state, state->pos) == '(') {
        token->type = _FUNCTION_CALL;
    }

    return token;
};
