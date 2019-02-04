#include <stdlib.h>
#include "includes/ast_node_interpreter_instr.h"


ast_node_interpreter_instr* init_ast_node_interpreter_instr(token* tok, char* name, char* value) {
    ast_node_interpreter_instr* ast;
    ast = calloc(1, sizeof(ast_node_interpreter_instr));
    ast->tok = tok;
    ast->name = name;
    ast->value = value;
    ast->base.type = AST_TYPE_INTERPRETER_INSTR;

    return ast;
}
