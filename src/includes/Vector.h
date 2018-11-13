#ifndef COLA_AST_NODE_VECTOR_H
#define COLA_AST_NODE_VECTOR_H
#define VECTOR_INITIAL_CAPACITY 100
#include "ast_node.h"

typedef struct {
    int size;
    int capacity;
    ast_node *data;
} Vector;

void vector_init(Vector *vector);

void vector_append(Vector *vector, ast_node* value);

ast_node vector_get(Vector *vector, int index);

void vector_double_capacity_if_full(Vector *vector);

void vector_free(Vector *vector);
#endif
