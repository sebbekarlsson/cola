#include "includes/interpret.h"
#include "includes/strutils.h"
#include "includes/ast_node.h"
#include "includes/error.h"
#include "includes/scope.h"
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
        case AST_TYPE_CHAR:
            return interpret_visit_char((ast_node_char*)node);
            break;
        case AST_TYPE_IF:
            return interpret_visit_if((ast_node_if*)node);
            break;
        case AST_TYPE_ELSE:
            return interpret_visit_else((ast_node_else*)node);
            break;
        case AST_TYPE_WHILE:
            return interpret_visit_while((ast_node_while*)node);
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

ast_node* interpret_visit_if(ast_node_if* node) {
    int expr_int = 0;
    ast_node* expr = interpret_visit(node->expr);
    if (expr->type == AST_TYPE_INTEGER) {
        ast_node_integer* tmp_ast = (ast_node_integer*) expr;
        expr_int = atoi(tmp_ast->tok->value);
        free(tmp_ast);
    }

    if (expr_int) {
        return interpret_visit((ast_node*)node->body);
    } else {
        return interpret_visit((ast_node*)node->elsenode);
    }

    return (ast_node*) init_ast_node_empty(node->tok);
};

ast_node* interpret_visit_else(ast_node_else* node) {
    if (node->ifnode) {
        return interpret_visit((ast_node*)node->ifnode);
    } else {
        return interpret_visit((ast_node*)node->body);
    }
}


ast_node* interpret_visit_while(ast_node_while* node) {
    int expr_int = 0;
    ast_node_integer* tmp_ast = (void*)0;

    ast_node* expr = interpret_visit((ast_node*) node->expr);
    if (expr->type == AST_TYPE_INTEGER) {
        tmp_ast = (ast_node_integer*) expr;
        expr_int = atoi(tmp_ast->tok->value);
    }

    while(expr_int) {
        interpret_visit((ast_node*)node->body);

        expr = interpret_visit((ast_node* )node->expr);
        if (expr->type == AST_TYPE_INTEGER) {
            tmp_ast = (ast_node_integer*) expr;
            expr_int = atoi(tmp_ast->tok->value);
        }
    }

    free(tmp_ast);

    return (ast_node*) init_ast_node_empty(node->tok);
}

ast_node* interpret_visit_char(ast_node_char* node) {
    return (ast_node*) node;
}

ast_node* interpret_visit_empty(ast_node_empty* node) {
    return (ast_node*) node;
}

ast_node* interpret_visit_compound(ast_node_compound* node) {
    for (int i = 0; i < node->nodes->size; i++) {
        ast_node* child_node = (ast_node*)node->nodes->items[i];
        interpret_visit(child_node);
    }

    return (ast_node*) node;
}

ast_node* interpret_visit_binop(ast_node_binop* node) {
    ast_node* left = node->left;
    ast_node* right = interpret_visit(node->right);

    if (node->tok->type == _EQUALS) {
        if (left->type != AST_TYPE_VARIABLE)
            error_in_interpreter("Can only use assign on variables");

        ast_node_variable* ast_var = (ast_node_variable*) left;

        ast_node_variable_definition* definition = get_variable_definition(
            (scope*) ast_node_get_scope((ast_node*)node),
            ast_var->tok->value
        );

        if (!definition)
            error_in_interpreter("Variables must be defined before they can be assigned");

        free(definition->value);
        definition->value = malloc(sizeof(right));
        definition->value = right;

    } else {
        left = interpret_visit(node->left);
    }

    if (left->type == AST_TYPE_INTEGER && right->type == AST_TYPE_INTEGER) {
        ast_node_integer* left_integer = (ast_node_integer*) left;
        ast_node_integer* right_integer = (ast_node_integer*) right;
        
        if (node->tok->type == _OP_PLUS) {
            sprintf(node->value, "%d", atoi(left_integer->tok->value) + atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value));
        } else if (node->tok->type == _OP_SUBTRACT) {
            sprintf(node->value, "%d", atoi(left_integer->tok->value) - atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value));
        } else if (node->tok->type == _OP_DIVIDE) {
            sprintf(node->value, "%d", atoi(left_integer->tok->value) / atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value));
        } else if (node->tok->type == _OP_MULTIPLY) {
            sprintf(node->value, "%d", atoi(left_integer->tok->value) * atoi(right_integer->tok->value));
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value));
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

        return value;
    } else {
        char msg[32];
        sprintf(msg, "could not find definition for: %s", node->tok->value);
        error_in_interpreter(msg);
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
        ss_vector* visited_args = ss_init_vector(sizeof(ast_node));

        for (int i = 0; i < node->args->size; i++) {
            ss_vector_append(
                visited_args,
                interpret_visit((ast_node*)node->args->items[i])
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

    // TODO: add type checking here
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
