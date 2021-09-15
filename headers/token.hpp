#pragma once

#include <string>


enum Token : char
{
    EXIT     =  0 ,
    ENTRY    = -1 ,
    NUM      = -2 ,
    STR      = -3 ,
    ID       = -4 ,
    EMPTY    = -5,
    LPAREN   = '(',
    RPAREN   = ')',
  //NEG,
  //POS,
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
    ADD      = '+',
    SUB      = '-',
    ASN      = ':',
    LBRACE   = '{',
    RBRACE   = '}',
    ENDL     = ';',
};
