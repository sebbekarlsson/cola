#include <stdlib.h>
#include "includes/token.h"


token* init_token(tokentype type, char* value) {
    token* tok;
    tok = malloc(sizeof(token));
    tok->type = type;
    tok->value = value;

    return tok;
}
