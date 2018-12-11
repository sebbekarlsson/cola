#ifndef AST_NODE_VECTOR
#define AST_NODE_VECTOR
#include "ast_node.h"
#include "ss_vector.h"


typedef struct AST_VECTOR_STRUCT {
    ast_node base;

    token* tok;
    int data_type;
    ss_vector* vector;
} ast_node_vector;


ast_node_vector* init_ast_node_vector(token* tok, int data_type, ss_vector* vector);
#endif
