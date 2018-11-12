#ifndef LEX_TOKEN_TYPE_H
#define LEX_TOKEN_TYPE_H
typedef enum {
    _EOF = 0,
    _ID,
    _INTEGER,
    _STRING,
    _OP_PLUS,
    _OP_SUBTRACT,
    _OP_MULTIPLY,
    _OP_DIVIDE,
    _OP_MOD,
    _OP_PERCENTAGE,
    _LPAREN,
    _RPAREN,
    _LBRACE,
    _RBRACE,
    _COMMA,
    _RETURN,
    _IF,
    _ELSE,
    _SEMI,
    _DOT,
    _AT,
    _LESS_THAN,
    _LARGER_THAN,
    _TYPE_STRING,
    _TYPE_INTEGER,
    _TYPE_FLOAT,
    _TYPE_VOID,
    _TYPE_STRUCT
} tokentype;
#endif
