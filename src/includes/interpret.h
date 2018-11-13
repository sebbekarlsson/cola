#ifndef INTERPRET_INTERPRET_H
#define INTERPRET_INTERPRET_H
#include "token.h"
#include "ast_node.h"
#include "ast_node_compound.h"
#include "ast_node_binop.h"
#include "ast_node_number.h"
#include "ast_node_integer.h"
#include "ast_node_component.h"


/*typedef struct INTERPRET_STATE_STRUCT {
    char* buffer;
    char current_char;
    int pos;
} interpret_state;


interpret_state* interpret_init();*/

ast_node* interpret_visit(ast_node* node);
ast_node* interpret_visit_compound(ast_node_compound* node);
ast_node* interpret_visit_binop(ast_node_binop* node);
ast_node* interpret_visit_number(ast_node_number* node);
ast_node* interpret_visit_integer(ast_node_integer* node);
ast_node* interpret_visit_component(ast_node_component* node);

#endif
