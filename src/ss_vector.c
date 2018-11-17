#include "includes/ss_vector.h"


ss_vector* ss_init_vector(size_t item_size) {
    ss_vector* vector;
    vector = malloc(sizeof(ss_vector));
    vector->size = 0;
    vector->items = calloc(0, item_size);

    return vector;
}


void ss_vector_append(ss_vector* vec, void* item) {
    vec->size++;
    vec->items = realloc(vec->items, vec->size * sizeof(item));
    vec->items[vec->size - 1] = item;
};


void ss_vector_free(ss_vector* vec) {
    for (int i = 0; i < vec->size; i++)
        free(vec->items[i]);

    free(vec->items);
    free(vec);
}
