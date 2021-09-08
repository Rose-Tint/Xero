#pragma once

#include <string>
#include <unordered_set>


struct oper_t;
struct expr_t;
struct token_t;


struct token_t
{
    const char opcode;
    std::string value;
};


struct oper_t
{
    std::string value;
    unsigned char precedence;
};


struct expr_t
{
    std::string value;
    oper_t op;
    Expr* left_op;
    Expr* right_op;
    ~Expr();
};


const std::unordered_set<char> pri_ops
{
    '!',
    '@',
    '#',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')',
    '-',
    '+',
    '=',
    '{',
    '}',
    '[',
    ']',
    '|',
    ':',
    ';',
    '<',
    '>',
    ',',
    '.',
    '/',
    '?'
};
