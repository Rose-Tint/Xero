#include "../headers/Lexer.hpp"
#include "consts.hpp"
#include <cctype>


bool Lexer::is_identifier(char c) const
{
    return std::isalnum(c) || c == '_';
}


bool Lexer::is_symbol(char c) const
{
    switch (c)
    {
        case '!':
        case '%':
        case '^':
        case '&':
        case '*':
        case '(':
        case ')':
        case '-':
        case '+':
        case '=':
        case '{':
        case '}':
        case '|':
        case '<':
        case '>':
        case '/':
            return true;
        default:
            return false;
    }
}
