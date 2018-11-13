#include "includes/parse_id.h"
#include "includes/tokentype.h"


token* parse_id(token* token) {
    if (strcmp(token->value, "string") == 0)
        token->type = _TYPE_STRING;
    else if (strcmp(token->value, "int") == 0)
        token->type = _TYPE_INTEGER;
    else if (strcmp(token->value, "float") == 0)
        token->type = _TYPE_FLOAT;
    else if (strcmp(token->value, "void") == 0)
        token->type = _TYPE_VOID;
    else if (strcmp(token->value, "struct") == 0)
        token->type = _TYPE_STRUCT;
    else if (strcmp(token->value, "comp") == 0)
        token->type = _TYPE_COMPONENT;
    else if (strcmp(token->value, "use") == 0)
        token->type = _USE;

    return token;
};
