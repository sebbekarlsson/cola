#include "includes/data_type_utils.h"
#include <string.h>


int name_to_data_type(char* name) {
    if (strcmp(name, "int") == 0) {
        return _DATA_TYPE_INTEGER;
    } else if (strcmp(name, "float") == 0) {
        return _DATA_TYPE_FLOAT;
    } else if (strcmp(name, "void") == 0) {
        return _DATA_TYPE_VOID;
    } else if (strcmp(name, "char") == 0) {
        return _DATA_TYPE_CHAR;
    } else if (strcmp(name, "string") == 0) {
        return _DATA_TYPE_STRING;
    } else {
        return -1;
    }
}
