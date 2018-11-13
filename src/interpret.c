#include "includes/interpret.h"
#include "includes/strutils.h"
#include <stdio.h>


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
    printf("visit binop\n");
    ast_node* left = node->left;
    ast_node* right = node->right;
    interpret_visit(left);
    interpret_visit(right);

    return (ast_node*) node;
}

ast_node* interpret_visit_number(ast_node_number* node) {
   printf("visit number\n");
   if (is_integer(node->tok->value))
       return (ast_node*) init_ast_node_integer(node->tok);

   return (ast_node*) node;
}

ast_node* interpret_visit_integer(ast_node_integer* node) {
    printf("visit integer\n");
    return (ast_node*) node;
}
