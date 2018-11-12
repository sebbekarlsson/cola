#ifndef LEX_TOKEN_H
#define LEX_TOKEN_H
#include <string.h>
#include "tokentype.h"


typedef struct token {
    tokentype type;
    char* value;
} token;


token* init_token(tokentype type, char *value);
#endif
