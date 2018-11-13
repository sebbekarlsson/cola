#include "includes/interpret.h"
#include "includes/strutils.h"
#include <stdio.h>
#include <stdlib.h>


ast_node* interpret_visit(ast_node* node) {
    if (!node) {
        printf("Encountered a NULL node\n");
        return (void*) 0;
    }
    
    switch (node->type) {
        case AST_TYPE_COMPOUND:
            return interpret_visit_compound((ast_node_compound*)node);
            break;
        case AST_TYPE_BINOP:
            return interpret_visit_binop((ast_node_binop*)node);
            break;
        case AST_TYPE_NUMBER:
            return interpret_visit_number((ast_node_number*)node);
            break;
        case AST_TYPE_INTEGER:
            return interpret_visit_integer((ast_node_integer*)node);
            break;
        default:
            printf("Unhandled AST node (%d)\n", node->type);
            return (void*)0;
            break;
    }

    return node;
}

ast_node* interpret_visit_compound(ast_node_compound* node) {
    for (int i = 0; i < node->nodes->size; i++) {
        ast_node* child_node = ast_array_get(node->nodes, i);
        interpret_visit(child_node);
    }

    return (ast_node*) node;
}

ast_node* interpret_visit_binop(ast_node_binop* node) {
    ast_node* left = node->left;
    ast_node* right = node->right;
    left = interpret_visit(left);
    right = interpret_visit(right);
    char buff[16];

    if (left->type == AST_TYPE_INTEGER && right->type == AST_TYPE_INTEGER) {
        ast_node_integer* left_integer = (ast_node_integer*) left;
        ast_node_integer* right_integer = (ast_node_integer*) right;
        
        if (node->tok->type == _OP_PLUS) {
            sprintf(buff, "%d", atoi(left_integer->tok->value) + atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(init_token(AST_TYPE_INTEGER, buff));
        } else if (node->tok->type == _OP_SUBTRACT) {
            sprintf(buff, "%d", atoi(left_integer->tok->value) - atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(init_token(AST_TYPE_INTEGER, buff)); 
        } else if (node->tok->type == _OP_DIVIDE) {
            sprintf(buff, "%d", atoi(left_integer->tok->value) / atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(init_token(AST_TYPE_INTEGER, buff)); 
        } else if (node->tok->type == _OP_MULTIPLY) {
            sprintf(buff, "%d", atoi(left_integer->tok->value) * atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(init_token(AST_TYPE_INTEGER, buff)); 
        }
    }

    return (ast_node*) node;
}

ast_node* interpret_visit_number(ast_node_number* node) {
   if (is_integer(node->tok->value))
       return interpret_visit((ast_node*) init_ast_node_integer(node->tok));

   return (ast_node*) node;
}

ast_node* interpret_visit_integer(ast_node_integer* node) {
    return (ast_node*) node;
}
