#ifndef TOKEN_HPP
#define TOKEN_HPP
enum Token : char
{
    EXIT     =  0 ,
    ENTRY    = -1 ,
    NUM      = -2 ,
    ID       = -4 ,
    EMPTY    = -5,
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
    ENDL     = ';',
};
#endif