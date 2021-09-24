#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>


enum Token
{
    EXIT     =  0 ,
    ENTRY    = -1 ,
    NUM      = -2 ,
    ID       = -4 ,
    EMPTY    = -5 ,
    STR      = -6 ,
    LPAREN   = '(',
    RPAREN   = ')',
    NOT      = '!',
    AND      = '&',
    OR       = '|',
    XOR      = '^',
    EQ       = '=',
    GT       = '>',
    LT       = '<',
    MOD      = '%',
    DIV      = '/',
    MUL      = '*',
    PLUS     = '+',
    MINUS    = '-',
    ASN      = ':',
    LBRACE   = '{',
    RBRACE   = '}',
    LBRACKET = '[',
    RBRACKET = ']',
    ENDL     = ';',
};

bool is_terminal(Token);

const char* ttos(Token);

#endif