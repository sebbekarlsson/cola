#ifndef COLA_ERROR_H
#define COLA_ERROR_H
void error(char* msg);
void error_in_lexer(char* msg);
void error_in_parser(char* msg);
void error_in_interpreter(char* msg);
#endif
