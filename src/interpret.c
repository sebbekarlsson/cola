#include "includes/interpret.h"
#include "includes/strutils.h"
#include "includes/scope.h"
#include "includes/ast_node.h"
#include <stdio.h>
#include <stdlib.h>


extern scope* global_scope;

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
        case AST_TYPE_EMPTY:
            return interpret_visit_empty((ast_node_empty*)node);
            break;
        case AST_TYPE_NUMBER:
            return interpret_visit_number((ast_node_number*)node);
            break;
        case AST_TYPE_INTEGER:
            return interpret_visit_integer((ast_node_integer*)node);
            break;
        case AST_TYPE_COMPONENT:
            return interpret_visit_component((ast_node_component*)node);
            break;
        case AST_TYPE_VARIABLE:
            return interpret_visit_variable((ast_node_variable*)node);
            break;
        case AST_TYPE_FUNCTION_CALL:
            return interpret_visit_function_call((ast_node_function_call*)node);
            break;
        case AST_TYPE_VARIABLE_DEFINITION:
            return interpret_visit_variable_definition((ast_node_variable_definition*)node);
            break;
        case AST_TYPE_FUNCTION_DEFINITION:
            return interpret_visit_function_definition((ast_node_function_definition*)node);
            break;
        default:
            printf("Unhandled AST node (%d)\n", node->type);
            return (void*)0;
            break;
    }

    return node;
}

ast_node* interpret_visit_empty(ast_node_empty* node) {
    return (ast_node*) node;
};

ast_node* interpret_visit_compound(ast_node_compound* node) {
    for (int i = 0; i < node->nodes->size; i++) {
        ast_node* child_node = ast_array_get(node->nodes, i);
        interpret_visit(child_node);
    }

    return (ast_node*) node;
}

ast_node* interpret_visit_binop(ast_node_binop* node) {
    ast_node* left = interpret_visit(node->left);
    ast_node* right = interpret_visit(node->right);

    if (left->type == AST_TYPE_INTEGER && right->type == AST_TYPE_INTEGER) {
        ast_node_integer* left_integer = (ast_node_integer*) left;
        ast_node_integer* right_integer = (ast_node_integer*) right;
        token* tok = left_integer->tok;
        
        if (node->tok->type == _OP_PLUS) {
            sprintf(tok->value, "%d", atoi(left_integer->tok->value) + atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(tok);
        } else if (node->tok->type == _OP_SUBTRACT) {
            sprintf(tok->value, "%d", atoi(left_integer->tok->value) - atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(tok); 
        } else if (node->tok->type == _OP_DIVIDE) {
            sprintf(tok->value, "%d", atoi(left_integer->tok->value) / atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(tok); 
        } else if (node->tok->type == _OP_MULTIPLY) {
            sprintf(tok->value, "%d", atoi(left_integer->tok->value) * atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(tok); 
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

ast_node* interpret_visit_component(ast_node_component* node) {
    if (node->deps->size == 0)
        free(node->deps);

    if (strcmp(node->name->value, "main") == 0)
        interpret_visit((ast_node*)node->body);

    return (ast_node*) node;
}

ast_node* interpret_visit_variable(ast_node_variable* node) {

    ast_node_variable_definition* definition = get_variable_definition(
        (scope*) ast_node_get_scope((ast_node*)node),
        node->tok->value
    );

    if (definition) {
        ast_node* value = interpret_visit(definition->value);

        // TODO: make this type-checking prettier

        if (definition->data_type == _DATA_TYPE_INTEGER && value->type != AST_TYPE_INTEGER) {
            printf("wrong data_type for %s\n", node->tok->value);
            return (void*)0; // TODO: exit program
        }

        if (definition->data_type == _DATA_TYPE_FLOAT && value->type != AST_TYPE_FLOAT) {
            printf("wrong data_type for %s\n", node->tok->value);
            return (void*)0; // TODO: exit program
        }

        if (definition->data_type == _DATA_TYPE_VOID && value->type != AST_TYPE_EMPTY) {
            printf("wrong data_type for %s\n", node->tok->value);
            return (void*)0; // TODO: exit program
        }

        return value;
    } else {
        printf("could not find definition for %s\n", node->tok->value);
    }

    return (ast_node*) node;
}

ast_node* interpret_visit_function_call(ast_node_function_call* node) {
    ast_node_function_definition* definition = get_function_definition(
        (scope*) ast_node_get_scope((ast_node*) node),
        node->tok->value 
    );

    if (!definition) {
        // definition not found in the nodes scope, so let's look for it
        // in the global scope.
        definition = get_function_definition(
            global_scope,
            node->tok->value
        );
    }

    if (definition) {
        ast_array* visited_args = init_ast_array();

        for (int i = 0; i < node->args->size; i++) {
            ast_array_append(
                visited_args,
                interpret_visit(ast_array_get(node->args, i))
            );
        }

        if (definition->call) {
            return interpret_visit(definition->call(visited_args));
        }
        return interpret_visit((ast_node*)definition->body);
    } else {
        printf("could not find definition for %s\n", node->tok->value);
        return (void*)0;
    }
}

ast_node* interpret_visit_variable_definition(ast_node_variable_definition* node) {
    node->value = interpret_visit(node->value);

    save_variable_definition(
        (scope*)ast_node_get_scope((
                ast_node*)node
         ),
        node
    );

    return (ast_node*) node;
}

ast_node* interpret_visit_function_definition(ast_node_function_definition* node) {
    //if (node->body) {
        // visit body
    //}

    save_function_definition(
        (scope*)ast_node_get_scope((
                ast_node*)node
         ),
        node
    );

    return (ast_node*) node;
}
