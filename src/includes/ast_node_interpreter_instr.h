#ifndef AST_NODE_INTERPRETER_INSTR
#define AST_NODE_INTERPRETER_INSTR
#include "ast_node.h"
typedef struct AST_INTERPRETER_INSTR_STRUCT {
    ast_node base;

    token* tok;
    char* name;
    char* value;
} ast_node_interpreter_instr;


ast_node_interpreter_instr* init_ast_node_interpreter_instr(
    token* tok,
    char* name,
    char* value
);
#endif
