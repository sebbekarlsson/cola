#include "includes/interpret.h"
#include "includes/strutils.h"
#include "includes/ast_node.h"
#include "includes/error.h"
#include "includes/scope.h"
#include <stdio.h>
#include <stdlib.h>


extern scope* global_scope;

/**
 * Main visit function.
 *
 * @param ast_node* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit(ast_node* node) {
    if (!node) {
        printf("Encountered a NULL node\n");
        return (void*) 0;
    }
    
    switch (node->type) {
        case AST_TYPE_RETURN:
            return interpret_visit_return((ast_node_return*)node);
            break;
        case AST_TYPE_COMPOUND:
            return interpret_visit_compound((ast_node_compound*)node);
            break;
        case AST_TYPE_BINOP:
            return interpret_visit_binop((ast_node_binop*)node);
            break;
        case AST_TYPE_EMPTY:
            return interpret_visit_empty((ast_node_empty*)node);
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
        case AST_TYPE_FOREACH:
            return interpret_visit_foreach((ast_node_foreach*)node);
            break;
        case AST_TYPE_INTEGER:
            return interpret_visit_integer((ast_node_integer*)node);
            break;
        case AST_TYPE_FLOAT:
            return interpret_visit_float((ast_node_float*)node);
            break;
        case AST_TYPE_STRING:
            return interpret_visit_string((ast_node_string*)node);
            break;
        case AST_TYPE_COMPONENT:
            return interpret_visit_component((ast_node_component*)node);
            break;
        case AST_TYPE_VECPTR:
            return interpret_visit_vecptr((ast_node_vecptr*)node);
            break;
        case AST_TYPE_VECTOR:
            return interpret_visit_vector((ast_node_vector*)node);
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

/**
 * Visit function for return statement
 *
 * @param ast_node_return* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_return(ast_node_return* node) {
    return interpret_visit(node->value);
};

/**
 * Visit function for if statement
 *
 * @param ast_node_if* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_if(ast_node_if* node) {
    int expr_int = 0;
    ast_node* expr = interpret_visit(node->expr);
    if (expr->type == AST_TYPE_INTEGER) {
        ast_node_integer* tmp_ast = (ast_node_integer*) expr;
        expr_int = tmp_ast->value;
        free(tmp_ast);
    }

    if (expr_int) {
        return interpret_visit((ast_node*)node->body);
    } else {
        return interpret_visit((ast_node*)node->elsenode);
    }

    return (ast_node*) init_ast_node_empty(node->tok);
};

/**
 * Visit function for else statement
 *
 * @param ast_node_else* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_else(ast_node_else* node) {
    if (node->ifnode) {
        return interpret_visit((ast_node*)node->ifnode);
    } else {
        return interpret_visit((ast_node*)node->body);
    }
}

/**
 * Visit function for while node
 *
 * @param ast_node_while* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_while(ast_node_while* node) {
    int expr_int = 0;
    ast_node_integer* tmp_ast = (void*)0;

    ast_node* expr = interpret_visit((ast_node*) node->expr);
    if (expr->type == AST_TYPE_INTEGER) {
        tmp_ast = (ast_node_integer*) expr;
        expr_int = tmp_ast->value;
    }

    while(expr_int) {
        interpret_visit((ast_node*)node->body);

        expr = interpret_visit((ast_node* )node->expr);
        if (expr->type == AST_TYPE_INTEGER) {
            tmp_ast = (ast_node_integer*) expr;
            expr_int = tmp_ast->value;
        }
    }

    // causes undefined behaviour
    //free(tmp_ast);

    return (ast_node*) init_ast_node_empty(node->tok);
}

/**
 * Visit function for foreach node
 *
 * @param ast_node_foreach* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_foreach(ast_node_foreach* node) {
    ast_node* final_result = (void*)0;
    ast_node* iterable = interpret_visit(node->iterable);
    token* value_name_tok = node->value_name;
    int counter = 0;
    int size = 0;


    scope* target_scope = (scope*)ast_node_get_scope((ast_node*)node->body);

    // we currently only support strings...
    // no other iterables exists yet! :)
    //
    // TODO: support more types
    if (iterable->type == AST_TYPE_STRING) {
        ast_node_string* iterable_string = (ast_node_string*) iterable;
        size = strlen(iterable_string->value);


        while (counter < size) {
            char current_char = iterable_string->value[counter];
            ast_node_char* current_item_char = init_ast_node_char(init_token(_CHAR, char_to_string(current_char)), current_char);

            // this is quite ugly, it deletes the definition and
            // sets the definition for every iteration in the loop.
            //
            // TODO: Make this prettier
            delete_variable_definition(target_scope, value_name_tok->value);
            ast_node_variable_definition* var_def = init_ast_node_variable_definition(
                value_name_tok,
                _DATA_TYPE_CHAR,
                (ast_node*) current_item_char        
            );
            save_variable_definition(target_scope, var_def);

            final_result = interpret_visit((ast_node*) node->body);
            counter++;
        }
    } else if (iterable->type == AST_TYPE_VECTOR) {
        ast_node_vector* iterable_vector = (ast_node_vector*) iterable;
        size = iterable_vector->vector->size;

        while (counter < size) {
            ast_node* current_node = iterable_vector->vector->items[counter];

            // this is quite ugly, it deletes the definition and
            // sets the definition for every iteration in the loop.
            //
            // TODO: Make this prettier
            delete_variable_definition(target_scope, value_name_tok->value);
            ast_node_variable_definition* var_def = init_ast_node_variable_definition(
                value_name_tok,
                iterable_vector->data_type,
                current_node 
            );
            save_variable_definition(target_scope, var_def);

            final_result = interpret_visit((ast_node*) node->body);
            counter++;
        }

    } else {
        error_in_interpreter("Does not know how to iterate data_type");
    }

    return final_result;
}

/**
 * Visit function for char node
 *
 * @param ast_node_char* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_char(ast_node_char* node) {
    return (ast_node*) node;
}

/**
 * Visit function for empty node
 *
 * @param ast_node_empty* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_empty(ast_node_empty* node) {
    return (ast_node*) node;
}

/**
 * Visit function for compound node
 *
 * @param ast_node_compound* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_compound(ast_node_compound* node) {
    for (int i = 0; i < node->nodes->size; i++) {
        ast_node* child_node = (ast_node*)node->nodes->items[i];

        if (child_node->type == AST_TYPE_RETURN) {
           return interpret_visit(child_node);
        } else { 
            interpret_visit(child_node);
        }
    }

    return (ast_node*) node;
}

/**
 * Visit function for binary operation node
 *
 * @param ast_node_binop* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_binop(ast_node_binop* node) {
    ast_node* left = node->left;
    ast_node* right = interpret_visit(node->right);
    ast_node_variable_definition* definition;

    if (node->tok->type == _EQUALS) {
        if (left->type != AST_TYPE_VARIABLE)
            error_in_interpreter("Can only use assign on variables");

        ast_node_variable* ast_var = (ast_node_variable*) left;

        definition = get_variable_definition(
            (scope*) ast_node_get_scope((ast_node*)node),
            ast_var->tok->value
        );

        if (!definition)
            error_in_interpreter("Variables must be defined before they can be assigned");

        // this causes undefined behaviour
        //free(definition->value);
        //definition->value = malloc(sizeof(right));
        ast_node* value = interpret_visit(right);

        if (
            (definition->data_type == _DATA_TYPE_INTEGER && value->type != AST_TYPE_INTEGER) ||
            (definition->data_type == _DATA_TYPE_FLOAT && value->type != AST_TYPE_FLOAT) ||
            (definition->data_type == _DATA_TYPE_VOID && value->type != AST_TYPE_EMPTY) ||
            (definition->data_type == _DATA_TYPE_STRING && value->type != AST_TYPE_STRING)
        ) {
            error_in_interpreter("Wrong data_type");
        }

        definition->value = value;
        return definition->value;
    }

    left = interpret_visit(node->left);

    if (left->type == AST_TYPE_INTEGER && right->type == AST_TYPE_INTEGER) {
        int left_integer = ((ast_node_integer*) left)->value;
        int right_integer = ((ast_node_integer*) right)->value;
        
        if (node->tok->type == _OP_PLUS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer + right_integer);
        } else if (node->tok->type == _OP_SUBTRACT) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer - right_integer);
        } else if (node->tok->type == _OP_DIVIDE) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer / right_integer);
        } else if (node->tok->type == _OP_MULTIPLY) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer * right_integer);
        } else if (node->tok->type == _EQUALS_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer == right_integer);
        } else if (node->tok->type == _NOT_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer != right_integer);
        } else if (node->tok->type == _LESS_THAN) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer < right_integer);
        } else if (node->tok->type == _LARGER_THAN) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer > right_integer);
        }
    } else if (left->type == AST_TYPE_FLOAT && right->type == AST_TYPE_FLOAT) {
        float left_float = ((ast_node_float*) left)->value;
        float right_float = ((ast_node_float*) right)->value;
        
        if (node->tok->type == _OP_PLUS) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_float + right_float);
        } else if (node->tok->type == _OP_SUBTRACT) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_float - right_float);
        } else if (node->tok->type == _OP_DIVIDE) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_float / right_float);
        } else if (node->tok->type == _OP_MULTIPLY) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_float * right_float);
        } else if (node->tok->type == _EQUALS_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_float == right_float);
        } else if (node->tok->type == _NOT_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_float != right_float);
        } else if (node->tok->type == _LESS_THAN) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_float < right_float);
        } else if (node->tok->type == _LARGER_THAN) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_float > right_float);
        }
    } else if (left->type == AST_TYPE_INTEGER && right->type == AST_TYPE_FLOAT) {
        int left_integer = ((ast_node_integer*) left)->value;
        float right_float = ((ast_node_float*) right)->value;
        
        if (node->tok->type == _OP_PLUS) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_integer + right_float);
        } else if (node->tok->type == _OP_SUBTRACT) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_integer - right_float);
        } else if (node->tok->type == _OP_DIVIDE) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_integer / right_float);
        } else if (node->tok->type == _OP_MULTIPLY) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_integer * right_float);
        } else if (node->tok->type == _EQUALS_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer == right_float);
        } else if (node->tok->type == _NOT_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer != right_float);
        } else if (node->tok->type == _LESS_THAN) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer < right_float);
        } else if (node->tok->type == _LARGER_THAN) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_integer > right_float);
        }
    } else if (left->type == AST_TYPE_FLOAT && right->type == AST_TYPE_INTEGER) {
        float left_float = ((ast_node_float*) left)->value;
        int right_integer = ((ast_node_integer*) right)->value;
        
        if (node->tok->type == _OP_PLUS) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_float + right_integer);
        } else if (node->tok->type == _OP_SUBTRACT) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_float - right_integer);
        } else if (node->tok->type == _OP_DIVIDE) {
            return (ast_node*) init_ast_node_float(init_token(_FLOAT, node->value), left_float / right_integer);
        } else if (node->tok->type == _OP_MULTIPLY) {
            return (ast_node*) init_ast_node_integer(init_token(_FLOAT, node->value), left_float * right_integer);
        } else if (node->tok->type == _EQUALS_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_float == right_integer);
        } else if (node->tok->type == _NOT_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_float != right_integer);
        } else if (node->tok->type == _LESS_THAN) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_float < right_integer);
        } else if (node->tok->type == _LARGER_THAN) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), left_float > right_integer);
        }
    } else if (left->type == AST_TYPE_STRING && right->type == AST_TYPE_STRING) {
        char* left_string = ((ast_node_string*) left)->value;
        char* right_string = ((ast_node_string*) right)->value;

        
        if (node->tok->type == _OP_PLUS) {
            strcat(left_string, right_string);
            return (ast_node*) init_ast_node_string(init_token(_STRING, node->value), left_string);
        } else if (node->tok->type == _EQUALS_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), strcmp(left_string, right_string) == 0);
        } else if (node->tok->type == _NOT_EQUALS) {
            return (ast_node*) init_ast_node_integer(init_token(_INTEGER, node->value), strcmp(left_string, right_string) != 0);
        }
    } else {
        error_in_interpreter("Invalid binop"); 
    }

    return (ast_node*) node;
}

/**
 * Visit function for integer node
 *
 * @param ast_node_integer* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_integer(ast_node_integer* node) {
    return (ast_node*) node;
}

/**
 * Visit function for float node
 *
 * @param ast_node_float* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_float(ast_node_float* node) {
    return (ast_node*) node;
}

/**
 * Visit function for string node
 *
 * @param ast_node_string* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_string(ast_node_string* node) {
    return (ast_node*) node;
}

/**
 * Visit function for component node
 *
 * @param ast_node_component* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_component(ast_node_component* node) {
    save_component((scope*)ast_node_get_scope((ast_node*)node), node);
    
    if (node->deps->size == 0) {
        free(node->deps);
    } else {
        for (int i = 0; i < node->deps->size; i++) {
            ast_node_component* component = get_component(
                (scope*)ast_node_get_scope((ast_node*)node),
                ((token*)node->deps->items[i])->value
            );

            if (!component) {
                char msg[32];
                sprintf(msg, "could not find definition for: %s", ((token*)node->deps->items[i])->value);
                error_in_interpreter(msg);
            }

            interpret_visit((ast_node*)component->body);
            scope* tmp_scope = (scope*)ast_node_get_scope((ast_node*) component->body);

            for (int ii = 0; ii < tmp_scope->functions->size; ii++) {
                save_function_definition(
                    (scope*)ast_node_get_scope((ast_node*)node->body),
                    (ast_node_function_definition*)tmp_scope->functions->items[ii]
                );   
            }

            // look for yields function
            ast_node_function_definition* yields_definition = get_function_definition(
                tmp_scope,
                "yields"
            );

            if (yields_definition) {
                // lets create a variable definition in the currently visited
                // component and assign whatever the yields method returns
                // to it.
                ast_node_variable_definition* var_definition = init_ast_node_variable_definition(
                    (token*)node->deps->items[i],
                    yields_definition->data_type,
                    interpret_visit((ast_node*)yields_definition->body)
                );
                ast_node_set_scope(
                    (ast_node*) var_definition,
                    (struct scope*)tmp_scope // should use same scope as the-
                    // - component it came from
                );

                // save whatever the yields method returns as a variable
                // in the currently visited component.
                save_variable_definition(
                    (scope*)ast_node_get_scope((ast_node*)node->body),
                    var_definition 
                );
            }
        }
    }

    // check if main component
    if (strcmp(node->name->value, "main") == 0)
        interpret_visit((ast_node*)node->body);


    // look for run method
    ast_node_function_definition* run_definition = get_function_definition(
        (scope*)ast_node_get_scope((ast_node*)node->body),
        "run"
    );

    if (run_definition)
        interpret_visit((ast_node*)run_definition->body);

    return (ast_node*) node;
}

/**
 * Visit function for vecptr node
 *
 * @param ast_node_vecptr* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_vecptr(ast_node_vecptr* node) {
    ast_node* target = interpret_visit(node->target);
    ast_node* index = interpret_visit(node->index);

    if (target->type == AST_TYPE_STRING) {
        ast_node_string* target_string = (ast_node_string*) target;
        if (index->type == AST_TYPE_INTEGER) {
            ast_node_integer* index_integer = (ast_node_integer*) index;
            char value = target_string->value[index_integer->value];
            char* strval = char_to_string(value);
            return (ast_node*) init_ast_node_char(init_token(_CHAR, strval), value);
        }
    }

    return (ast_node*) interpret_visit(node->target);
}

/**
 * Visit function for vector node
 *
 * @param ast_node_vector* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_vector(ast_node_vector* node) {
    return (ast_node*) node;
}

/**
 * Visit function for variable node
 *
 * @param ast_node_variable* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_variable(ast_node_variable* node) {

    ast_node_variable_definition* definition = get_variable_definition(
        (scope*) ast_node_get_scope((ast_node*)node),
        node->tok->value
    );

    if (!definition) {
        // definition not found in the nodes scope, so let's look for it
        // in the global scope.
        definition = get_variable_definition(
            global_scope,
            node->tok->value
        );
    }

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

/**
 * Visit function for function call node
 *
 * @param ast_node_function_call* node
 *
 * @return ast_node*
 */
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

/**
 * Visit function for variable definition node
 *
 * @param ast_node_variable_definition* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_variable_definition(ast_node_variable_definition* node) {
    node->value = interpret_visit(node->value);

    node->value = interpret_visit(node->value);

    if (
        (node->data_type == _DATA_TYPE_INTEGER && node->value->type != AST_TYPE_INTEGER) ||
        (node->data_type == _DATA_TYPE_FLOAT && node->value->type != AST_TYPE_FLOAT) ||
        (node->data_type == _DATA_TYPE_VOID && node->value->type != AST_TYPE_EMPTY) ||
        (node->data_type == _DATA_TYPE_STRING && node->value->type != AST_TYPE_STRING)
    ) {
        error_in_interpreter("Wrong data_type");
    }

    save_variable_definition(
        (scope*)ast_node_get_scope((
                ast_node*)node
         ),
        node
    );

    return (ast_node*) node;
}

/**
 * Visit function for function definition node
 *
 * @param ast_node_function_definition* node
 *
 * @return ast_node*
 */
ast_node* interpret_visit_function_definition(ast_node_function_definition* node) {
    save_function_definition(
        (scope*)ast_node_get_scope((
                ast_node*)node
         ),
        node
    );

    return (ast_node*) node;
}
