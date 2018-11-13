#include "includes/parse_id.h"
#include "includes/tokentype.h"


token* parse_id(token* token) {
    if (
        strcmp(token->value, "string") == 0 ||
        strcmp(token->value, "int") == 0 ||
        strcmp(token->value, "struct") == 0 ||
        strcmp(token->value, "void") == 0 ||
        strcmp(token->value, "float") == 0
    ) {
        token->type = _DATA_TYPE;
    } else if (strcmp(token->value, "comp") == 0) {
        token->type = _TYPE_COMPONENT;
    } else if (strcmp(token->value, "use") == 0) {
        token->type = _USE;
    }

    return token;
};
