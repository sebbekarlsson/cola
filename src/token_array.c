#include "includes/token_array.h"
#include <stdlib.h>


token_array* init_token_array() {
    token_array* tokenarr;
    tokenarr = malloc(sizeof(token_array));
    tokenarr->elements = calloc(0, sizeof(token));
    tokenarr->size = 0;
    tokenarr->memsize = 0;

    return tokenarr;
};

int token_array_append(token_array* tokenarr, token* node) {
    tokenarr->elements = realloc(tokenarr->elements, (tokenarr->memsize * sizeof(token*)) + sizeof(token*));
    tokenarr->elements[tokenarr->size] = node;
    tokenarr->memsize++;
    tokenarr->size++;

    return tokenarr->size;
};

token* token_array_get(token_array* tokenarr, int index) {
    return tokenarr->elements[index];
};
