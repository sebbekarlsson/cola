/** ==========================================================================
 * PURPOSE: This file is used to initialize / populate the default scope with
 * built-in methods, variables etc.
 ========================================================================== */ 
#include "includes/default_scope_initialize.h"
#include "includes/scope.h"
#include "includes/ast_node_integer.h"
#include "includes/ast_node_float.h"
#include "includes/ast_node_empty.h"
#include "includes/ast_node_char.h"
#include "includes/ast_node_string.h"
#include "includes/ast_node_vector.h"
#include <stdio.h>

/**
 * Built-in method for printing to stdout with a new line.
 * It handles different types of values.
 *
 * @param ss_vector* args
 *
 * @return ast_node*
 */
ast_node* _print(ss_vector* args) {
    for (int i = 0; i < args->size; i++) {
        ast_node* node = (ast_node*)args->items[i];

        if (node->type == AST_TYPE_INTEGER) {
            ast_node_integer* node_integer = (ast_node_integer*) node;
            printf("%d\n", node_integer->value);
        } else if (node->type == AST_TYPE_FLOAT) {
            ast_node_float* node_float = (ast_node_float*) node;
            printf("%f\n", node_float->value);
        } else if (node->type == AST_TYPE_CHAR) {
            ast_node_char* node_char = (ast_node_char*) node;
            printf("%c\n", node_char->value);
        } else if (node->type == AST_TYPE_STRING) {
            ast_node_string* node_string = (ast_node_string*) node;
            printf("%s\n", node_string->value);
        } else {
            printf("<%d>\n", (int)node->type);
        }
    }

    return (ast_node*) init_ast_node_empty((void*)0);
};

/**
 * Built-in method to get the size of a string as a integer.
 *
 * param string
 *
 * return integer
 *
 * --------
 *
 * @param ss_vector* args
 *
 * @return ast_node*
 */
ast_node* _strlen(ss_vector* args) {
    ast_node* _node = (ast_node*)args->items[0];

    if (_node->type != AST_TYPE_STRING)
        return (ast_node*) init_ast_node_empty((void*)0); 

    ast_node_string* node_string = (ast_node_string*) _node;

    int length = strlen(node_string->value);

    return (ast_node*) init_ast_node_integer(
        init_token(_INTEGER, ""),
        length
    );
};

/**
 * Built-in method to split a string.
 *
 * param string str
 * param string delim
 *
 * --------
 *
 * @param ss_vector* args
 *
 * @return ast_node*
 */
ast_node* _strsplit(ss_vector* args) {
    ast_node* _node0 = (ast_node*)args->items[0];
    ast_node* _node1 = (ast_node*)args->items[1];

    if (_node0->type != AST_TYPE_STRING)
        return (ast_node*) init_ast_node_empty((void*)0);

    if (_node1->type != AST_TYPE_STRING)
        return (ast_node*) init_ast_node_empty((void*)0);


    ast_node_string* node_string0 = (ast_node_string*) _node0;
    ast_node_string* node_string1 = (ast_node_string*) _node1;

    ss_vector* items = ss_init_vector(sizeof(ast_node));

    char* token;
    token = strtok(node_string0->value, node_string1->value);

    ast_node_string* item_str = init_ast_node_string(
        (void*)0,
        token
    );
    ss_vector_append(items, (ast_node*) item_str);

    while (token != NULL) {
        token = strtok(NULL, node_string1->value);

        if (!token)
            continue;

        ast_node_string* item_str = init_ast_node_string(
            (void*)0,
            token
        );
        ss_vector_append(items, (ast_node*) item_str);
    }

    return (ast_node*) init_ast_node_vector(
        (void*)0,
        _DATA_TYPE_VECTOR,
        items        
    );
};

/**
 * This method is used to populate a scope with built-in:s.
 *
 * param string
 *
 * return integer
 *
 * --------
 *
 * @param scope* sc
 */
void default_scope_initialize(scope* sc) {

    ss_vector* args = ss_init_vector(sizeof(ast_node));

    ast_node_function_definition* print_definition = init_ast_node_function_definition(
        init_token(_ID, "print"),
        _DATA_TYPE_VOID,
        args,
        (void*)0
    );

    print_definition->call = _print;
    save_function_definition(sc, print_definition);

    ast_node_function_definition* strlen_definition = init_ast_node_function_definition(
        init_token(_ID, "strlen"),
        _DATA_TYPE_INTEGER,
        args,
        (void*)0
    );

    strlen_definition->call = _strlen;
    save_function_definition(sc, strlen_definition);

    ast_node_function_definition* strsplit_definition = init_ast_node_function_definition(
        init_token(_ID, "strsplit"),
        _DATA_TYPE_VECTOR,
        args,
        (void*)0
    );

    strsplit_definition->call = _strsplit;
    save_function_definition(sc, strsplit_definition);
}
