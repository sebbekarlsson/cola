#ifndef SS_VECTOR_H
#define SS_VECTOR_H
#include <stdlib.h>
typedef struct STRUCT_SS_VECTOR {
    size_t size;
    void** items;
} ss_vector;

ss_vector* ss_init_vector(size_t item_size);

void ss_vector_append(ss_vector* vec, void* item);

void ss_vector_free(ss_vector* vec);
#endif
