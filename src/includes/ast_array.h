#ifndef AST_ARRAY_H
#define AST_ARRAY_H
#include "ast_node.h"

typedef struct AST_ARRAY_STRUCT {
    unsigned int size;
    size_t memsize;
    ast_node** elements;
} ast_array;

ast_array* init_ast_array();

int ast_array_append(ast_array* astarr, ast_node* node);

ast_node* ast_array_get(ast_array* astarr, int index);

#endif
