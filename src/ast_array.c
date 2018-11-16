#include "includes/ast_array.h"
#include <stdlib.h>


ast_array* init_ast_array() {
    ast_array* astarr;
    astarr = malloc(sizeof(ast_array));
    astarr->elements = calloc(0, sizeof(ast_node));
    astarr->size = 0;
    astarr->memsize = 0;

    return astarr;
};

int ast_array_append(ast_array* astarr, ast_node* node) {
    astarr->elements = realloc(astarr->elements, (astarr->memsize * sizeof(ast_node*)) + sizeof(ast_node*));
    astarr->elements[astarr->size] = node;
    astarr->memsize++;
    astarr->size++;

    return astarr->size;
};

ast_node* ast_array_get(ast_array* astarr, int index) {
    return astarr->elements[index];
};
