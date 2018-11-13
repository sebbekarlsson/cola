#ifndef TOKEN_ARRAY_H
#define TOKEN_ARRAY_H
#include "token.h"

typedef struct TOKEN_ARRAY_STRUCT {
    unsigned int size;
    token* elements[];
} token_array;

token_array* init_token_array();

int token_array_append(token_array* tokenarr, token* node);

token* token_array_get(token_array* tokenarr, int index);

#endif
