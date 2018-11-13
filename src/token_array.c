#include "includes/token_array.h"
#include <stdlib.h>


token_array* init_token_array() {
    token_array* tokenarr;
    tokenarr = malloc(sizeof(token_array));
    tokenarr->size = 0;

    return tokenarr;
};

int token_array_append(token_array* tokenarr, token* node) {
    tokenarr->elements[tokenarr->size] = node;
    tokenarr->size++;

    return tokenarr->size;
};

token* token_array_get(token_array* tokenarr, int index) {
    return tokenarr->elements[index];
};
