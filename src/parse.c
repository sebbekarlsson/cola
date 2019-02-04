#include "includes/parse.h"
#include "includes/token.h"
#include "includes/error.h"
#include "includes/ss_vector.h"
#include "includes/data_type_utils.h"
#include "includes/ast_node_binop.h"
#include "includes/ast_node_unaryop.h"
#include "includes/ast_node_empty.h"
#include "includes/ast_node_char.h"
#include "includes/ast_node_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


parse_state* parse_init(lex_state* lex) {
    parse_state* state;
    state = malloc(sizeof(struct PARSE_STATE_STRUCT));
    state->lex = lex;
    state->current_token = lex_get_next_token(state->lex);

    return state;
};

void parse_eat(parse_state* state, int token_type) {
    if (state->current_token->type == token_type) {
        state->current_token = lex_get_next_token(state->lex);
    } else {
        printf("Unexpected token_type: `%d` (was expecting `%d`)\n", state->current_token->type, token_type);
        // TODO: error
    }
};

ast_node_integer* parse_integer(parse_state* state, scope* sc) {
    ast_node_integer* node = init_ast_node_integer(state->current_token, atoi(state->current_token->value));
    parse_eat(state, _INTEGER);
    ast_node_set_scope((ast_node*) node, (struct scope*) sc);
    return node;
}

ast_node_vecptr* parse_vecptr(parse_state* state, scope* sc) {
    ast_node* target = parse_expr(state, sc);
    parse_eat(state, _LBRACKET);
    ast_node* index = (ast_node*) parse_expr(state, sc);
    parse_eat(state, _RBRACKET);

    ast_node_vecptr* vecptr_node = init_ast_node_vecptr(
        (void*)0,
        target,
        index
    );

    ast_node_set_scope((ast_node*)vecptr_node, (struct scope*) sc);

    return vecptr_node;
}


ast_node_vector* parse_vector(parse_state* state, scope* sc) {
    parse_eat(state, _LBRACKET);
    ss_vector* items = ss_init_vector(sizeof(ast_node));
    
    ss_vector_append(items, (ast_node*) parse_expr(state, sc));
    
    while (state->current_token->type == _COMMA) {
        parse_eat(state, _COMMA);
        ss_vector_append(items, (ast_node*) parse_expr(state, sc));
    }

    parse_eat(state, _RBRACKET);

    ast_node_vector* node = init_ast_node_vector(
        state->current_token,
        0,
        items
    );

    ast_node_set_scope((ast_node*) node, (struct scope*) sc);

    return node;
}

ast_node_float* parse_float(parse_state* state, scope* sc) {
    ast_node_float* node = init_ast_node_float(state->current_token, atof(state->current_token->value));
    parse_eat(state, _FLOAT);
    ast_node_set_scope((ast_node*) node, (struct scope*) sc);
    return node;
}

ast_node_return* parse_return(parse_state* state, scope* sc) {
    parse_eat(state, _RETURN);
    ast_node* expr = parse_expr(state, sc);

    ast_node_return* return_ast = init_ast_node_return(
        state->current_token,
        expr
    );

    ast_node_set_scope((ast_node*) return_ast, (struct scope*) sc);

    return return_ast;
}

ast_node_while* parse_while(parse_state* state, scope* sc) {
    parse_eat(state, _WHILE);
    parse_eat(state, _LPAREN);
    ast_node* expr = parse_expr(state, sc);
    parse_eat(state, _RPAREN);
    parse_eat(state, _LBRACE);

    ast_node_compound* body = parse_compound(state, sc);
    ast_node_set_scope((ast_node*) body, (struct scope*) sc);

    parse_eat(state, _RBRACE);

    ast_node_while* while_ast = init_ast_node_while(
        state->current_token,
        expr,
        body
    );

    ast_node_set_scope((ast_node*) while_ast, (struct scope*) sc);

    return while_ast;
}

ast_node_foreach* parse_foreach(parse_state* state, scope* sc) {
    parse_eat(state, _FOREACH);
    parse_eat(state, _LPAREN);
    ast_node* iterable = parse_expr(state, sc);
    parse_eat(state, _AS);
    token* value_name_tok = state->current_token;
    parse_eat(state, _ID);
    parse_eat(state, _RPAREN);
    parse_eat(state, _LBRACE);
    ast_node_compound* body = parse_compound(state, sc);
    parse_eat(state, _RBRACE);

    ast_node_foreach* foreach_ast = init_ast_node_foreach(
        value_name_tok,
        iterable,
        value_name_tok,
        body        
    );

    ast_node_set_scope((ast_node*) foreach_ast, (struct scope*) sc);

    return foreach_ast;
}

ast_node_else* parse_else(parse_state* state, scope* sc) {
    parse_eat(state, _ELSE);
    ast_node_if* ifnode = (void*)0;
    ast_node_compound* body = (void*)0;

    if (state->current_token->type == _IF) {
        ifnode = parse_if(state, sc);
    } else {
        parse_eat(state, _LBRACE);
        body =  parse_compound(state, sc);
        parse_eat(state, _RBRACE);
    }

    ast_node_else* else_ast = init_ast_node_else(
        state->current_token,
        body,
        (struct ast_node_if*) ifnode
    );

    ast_node_set_scope((ast_node*) else_ast, (struct scope*) sc);

    return else_ast;
}

ast_node_if* parse_if(parse_state* state, scope* sc) {
    parse_eat(state, _IF);
    parse_eat(state, _LPAREN);
    ast_node* expr = parse_expr(state, sc);
    parse_eat(state, _RPAREN);
    parse_eat(state, _LBRACE);
    ast_node_compound* body =  parse_compound(state, sc);
    parse_eat(state, _RBRACE);

    ast_node_else* elsenode = (void*)0;

    if (state->current_token->type == _ELSE)
        elsenode = parse_else(state, sc);

    ast_node_if* if_ast = init_ast_node_if(
        state->current_token,
        expr,
        body,
        elsenode
    );

    ast_node_set_scope((ast_node*) if_ast, (struct scope*) sc);

    return if_ast;
}

ast_node_variable* parse_variable(parse_state* state, scope* sc) {
    ast_node_variable* var = init_ast_node_variable(state->current_token, (void*)0);
    parse_eat(state, _ID);

    ast_node_set_scope((ast_node*) var, (struct scope*) sc);

    return var;
};

ast_node_function_call* parse_function_call(parse_state* state, scope* sc) {
    token* tok = state->current_token;
    parse_eat(state, _FUNCTION_CALL);
    ss_vector* args = ss_init_vector(sizeof(ast_node));

    parse_eat(state, _LPAREN);

    if (state->current_token->type != _RPAREN) {
        ss_vector_append(args, (ast_node*) parse_expr(state, sc));

        while (state->current_token->type == _COMMA) {
            parse_eat(state, _COMMA);
            ss_vector_append(args, (ast_node*) parse_expr(state, sc));
        }
    }

    parse_eat(state, _RPAREN);

    ast_node_function_call* call = init_ast_node_function_call(
        tok,
        args
    );

    ast_node_set_scope((ast_node*)call, (struct scope*) sc);

    return call;
}

ast_node* parse_factor(parse_state* state, scope* sc) {
    token* tok = state->current_token;

    if (tok->type == _OP_PLUS) {
        parse_eat(state, _OP_PLUS);
        ast_node_unaryop* node = init_ast_node_unaryop(tok, parse_factor(state, sc));
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
        // invalid pointer type
        return (ast_node*) node;

    } else if (tok->type == _OP_SUBTRACT) {
        parse_eat(state, _OP_SUBTRACT);
        ast_node_unaryop* node = init_ast_node_unaryop(tok, parse_factor(state, sc));
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
        // invalid pointer type
        return (ast_node*) node;

    } else if (tok->type == _NOT_EQUALS) {
        parse_eat(state, _NOT_EQUALS);
        ast_node_unaryop* node = init_ast_node_unaryop(tok, parse_factor(state, sc));
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
        // invalid pointer type
        return (ast_node*) node;

    } else if (tok->type == _INTEGER) {
        return (ast_node*) parse_integer(state, sc);
    } else if (tok->type == _FLOAT) {
        return (ast_node*) parse_float(state, sc);
    } else if (tok->type == _CHAR) {
        parse_eat(state, _CHAR);
        ast_node_char* node = init_ast_node_char(tok, tok->value[0]);
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
        // invalid pointer type
        return (ast_node*) node;

    } else if (tok->type == _STRING) {
        parse_eat(state, _STRING);
        ast_node_string* node = init_ast_node_string(tok, tok->value);
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
        // invalid pointer type
        return (ast_node*) node;
    
    } else if (tok->type == _TYPE_COMPONENT) {
        return (ast_node*) parse_component(state, sc);
    } else if (tok->type == _ID) {
        return (ast_node*) parse_variable(state, sc);
    } else if (tok->type == _FUNCTION_CALL) {
        return (ast_node*) parse_function_call(state, sc);
    } else if (tok->type == _LPAREN) {
        parse_eat(state, _LPAREN);
        ast_node* node = parse_expr(state, sc);
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
        parse_eat(state, _RPAREN);
        return node;
    } else if (tok->type == _LBRACKET) {
        ast_node_vector* node = parse_vector(state, sc);
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
        return (ast_node*) node;
    } else {
        printf("Unexpected token_type: `%d`\n", tok->type);
        return (void*)0;
    }

    return (ast_node*) parse_expr(state,sc );
}

ast_node* parse_term(parse_state* state, scope* sc) {
    token* tok = (void*)0;

    ast_node* node = parse_factor(state, sc);

    if (state->current_token->type == _EQUALS) {
        token* tok = state->current_token;
        parse_eat(state, _EQUALS);
        ast_node* assign_node = (ast_node*)  init_ast_node_binop(tok, node, parse_expr(state, sc));
        ast_node_set_scope((ast_node*) assign_node, (struct scope*) sc);
        return assign_node;
    } 

    while (
            state->current_token->type == _OP_MULTIPLY ||
            state->current_token->type == _OP_DIVIDE
          ) {
        tok = state->current_token;

        if (tok->type == _OP_MULTIPLY) {
            parse_eat(state, _OP_MULTIPLY);
        } else if (tok->type == _OP_DIVIDE) {
            parse_eat(state, _OP_DIVIDE);
        }

        // this probably wont work since `node` is of pointer type ast_node*
        node = (ast_node*) init_ast_node_binop(tok, node, parse_factor(state, sc));
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
    }

    return (ast_node*) node;
}

ast_node* parse_expr(parse_state* state, scope* sc) {
    token* tok = (void*)0;

    // invalid pointer type
    ast_node* node = parse_term(state, sc);

    if (state->current_token->type == _LBRACKET) {
        tok = state->current_token;
        parse_eat(state, _LBRACKET);
        ast_node_vecptr* vecptrnode = init_ast_node_vecptr((void*)0, node, parse_expr(state, sc));
        parse_eat(state, _RBRACKET);
        return (ast_node*) vecptrnode;
    }

    while(
            state->current_token->type == _OP_PLUS ||
            state->current_token->type == _OP_SUBTRACT ||
            state->current_token->type == _NOT_EQUALS ||
            state->current_token->type == _LESS_THAN ||
            state->current_token->type == _LARGER_THAN ||
            state->current_token->type == _LESS_OR_EQUALS ||
            state->current_token->type == _LARGER_OR_EQUALS ||
            state->current_token->type == _EQUALS_EQUALS ||
            state->current_token->type == _DOT
         ) {
        tok = state->current_token;

        if (tok->type == _OP_PLUS) {
            parse_eat(state, _OP_PLUS);
        } else if (tok->type == _OP_SUBTRACT) {
            parse_eat(state, _OP_SUBTRACT);
        } else if (tok->type == _NOT_EQUALS) {
            parse_eat(state, _NOT_EQUALS);
        } else if (tok->type == _LESS_THAN) {
            parse_eat(state, _LESS_THAN);
        } else if (tok->type == _LARGER_THAN) {
            parse_eat(state, _LARGER_THAN);
        } else if (tok->type == _LESS_OR_EQUALS) {
            parse_eat(state, _LESS_OR_EQUALS);
        } else if (tok->type == _LARGER_OR_EQUALS) {
            parse_eat(state, _LARGER_OR_EQUALS);
        } else if (tok->type == _EQUALS_EQUALS) {
            parse_eat(state, _EQUALS_EQUALS);
        } else if (tok->type == _DOT) {
            parse_eat(state, _DOT);
        }

        // invalid pointer type
        node = (ast_node*) init_ast_node_binop(tok, node, parse_term(state, sc));
        ast_node_set_scope((ast_node*) node, (struct scope*) sc);
    };

    return node;
}

ast_node* parse_statement(parse_state* state, scope* sc) {
    if (state->current_token->type == _INTERPRETER_INSTR) {
        return (ast_node*) parse_interpreter_instr(state, sc);
    } else if (state->current_token->type == _RETURN) {
        return (ast_node*) parse_return(state, sc);
    } else if (state->current_token->type == _TYPE_COMPONENT) {
        return (ast_node*) parse_component(state, sc);
    } else if (state->current_token->type == _IF) {
        return (ast_node*) parse_if(state, sc);
    } else if (state->current_token->type == _WHILE) {
        return (ast_node*) parse_while(state, sc);
    } else if (state->current_token->type == _FOREACH) {
        return (ast_node*) parse_foreach(state, sc);
    } else if (state->current_token->type == _DATA_TYPE) {
        return (ast_node*) parse_variable_definition(state, sc);
    } else if (state->current_token->type == _TYPE_FUNCTION) {
        return (ast_node*) parse_function_definition(state, sc);
    }  else if (state->current_token->type == _FUNCTION_CALL) {
        return (ast_node*) parse_function_call(state, sc);
    } else if (state->current_token->type == _ID || state->current_token->type == _INTEGER || state->current_token->type == _FLOAT) {
        return parse_expr(state, sc);
    } else {
        return (void*)0;
    }
};

ss_vector* parse_statement_list(parse_state* state, scope* sc) {
    ss_vector* nodes = ss_init_vector(sizeof(ast_node));

    ss_vector_append(nodes, parse_statement(state, sc));

    while (state->current_token->type == _SEMI) {
        parse_eat(state, _SEMI);

        ast_node* next_statement = parse_statement(state, sc);

        if (!next_statement)
            break;

        ss_vector_append(nodes, next_statement);
    }

    return nodes;
};

ast_node_compound* parse_compound(parse_state* state, scope* sc) {
    return init_ast_node_compound(
        (void*)0, parse_statement_list(state, sc)
    );
};

ast_node_component* parse_component(parse_state* state, scope* sc) {
    parse_eat(state, _TYPE_COMPONENT);

    sc = init_scope();
    
    token* name = state->current_token;
    parse_eat(state, _ID);

    ss_vector* deps = ss_init_vector(sizeof(token));

    if (state->current_token->type == _USE) {
        parse_eat(state, _USE);
        ss_vector_append(deps, state->current_token);
        parse_eat(state, _ID); 

        while (state->current_token->type == _COMMA) {
            parse_eat(state, _COMMA);
            parse_eat(state, _ID); 
            ss_vector_append(deps, state->current_token);
        }
    }

    parse_eat(state, _LBRACE);
    ast_node_compound* body = parse_compound(state, sc);
    ast_node_set_scope((ast_node*)body, (struct scope*)sc);

    parse_eat(state, _RBRACE);

    ast_node_component* component = init_ast_node_component(
        name,
        name,
        body,
        deps
    );
    
    //ast_node_set_scope((ast_node*)component, (struct scope*)sc);

    return component;
};

ast_node_variable_definition* parse_variable_definition(parse_state* state, scope* sc) {
    char* data_type_name = state->current_token->value;
    int data_type = name_to_data_type(data_type_name);
    ast_node* value;

    parse_eat(state, _DATA_TYPE);

    if (data_type == _DATA_TYPE_VECTOR) {
        parse_eat(state, _LESS_THAN);
        //char* vector_data_type_name = state->current_token->value;
        parse_eat(state, _DATA_TYPE);
        //int vector_data_type = name_to_data_type(vector_data_type_name);
        parse_eat(state, _LARGER_THAN);
    }

    token* tok = state->current_token;
    parse_eat(state, _ID);

    if (state->current_token->type == _EQUALS) {
        parse_eat(state, _EQUALS);
        value = parse_expr(state, sc);
    } else {
        value = (ast_node*) init_ast_node_empty((void*)0);
    }

    ast_node_variable_definition* definition = init_ast_node_variable_definition(
        tok,
        data_type,
        value
    );

    ast_node_set_scope((ast_node*)definition, (struct scope*) sc);

    return definition;
}

ast_node_function_definition* parse_function_definition(parse_state* state, scope* sc) {
    parse_eat(state, _TYPE_FUNCTION);

    char* data_type_name = state->current_token->value;
    int data_type = name_to_data_type(data_type_name);
    ast_node_compound* body;
    ss_vector* args = ss_init_vector(sizeof(ast_node));

    parse_eat(state, _DATA_TYPE);
    token* tok = state->current_token;
    parse_eat(state, _ID);

    if (state->current_token->type == _LPAREN) {
        parse_eat(state, _LPAREN);
       
        ss_vector_append(args, (ast_node*) parse_variable_definition(state, sc));

        while (state->current_token->type == _COMMA) {
            parse_eat(state, _COMMA);
            ss_vector_append(args, (ast_node*) parse_variable_definition(state, sc));
        }
    }

    parse_eat(state, _LBRACE);
    body = parse_compound(state, sc);
    parse_eat(state, _RBRACE);

    ast_node_function_definition* definition = init_ast_node_function_definition(
        tok,
        data_type,
        args,
        body 
    );

    ast_node_set_scope((ast_node*) definition, (struct scope*)sc);

    return definition;
};

ast_node_interpreter_instr* parse_interpreter_instr(parse_state* state, scope* sc) {
    token* tok = state->current_token;
    char* instruction_name = tok->value;

    // TODO: make this better, give the user some information about which
    // instruction name that was unknown.
    if (strcmp(instruction_name, "include") != 0)
        error_in_parser("Unknown instruction name");

    parse_eat(state, _INTERPRETER_INSTR);
    char* instruction_value = state->current_token->value;
    parse_eat(state, _STRING);

    ast_node_interpreter_instr* instr = init_ast_node_interpreter_instr(
        tok,
        instruction_name,
        instruction_value        
    );
    
    ast_node_set_scope((ast_node*) instr, (struct scope*)sc);

    return instr;
}

ast_node_compound* parse_parse(parse_state* state, scope* sc) {
    return parse_compound(state, sc);
}
