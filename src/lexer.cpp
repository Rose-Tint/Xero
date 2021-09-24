#include "lexer.hpp"
#include "error.hpp"
#include <iostream>


Lexer::Lexer(std::stringstream& input) : code(input) { }


bool Lexer::is_symbol(char c) const
{
    switch (c)
    {
        case ';':
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
        case ':':
        case '[':
        case ']':
            return true;
        default:
            return false;
    }
}


std::string Lexer::make_number()
{
    std::string str;
    unsigned int num;
    code >> num;
    str = std::to_string(num);
    if (code.peek() == '.')
    {
        code >> num;
        str.append(std::to_string(num));
    }
    return str;
}


std::string Lexer::make_id()
{
    std::string str;
    char c;
    while (code.get(c))
    {
        if (!is_identifier(c))
        {
            code.unget();
            break;
        }
        str += c;
    }
    return str;
}


std::string Lexer::make_string()
{
    std::string str;
    char c = code.get(); // skips str intializing token
    while (code.get(c))
    {
        if (c == '"' || c == '\'') break;
        str += c;
    }
    return str;
}


Token Lexer::next()
{
    if (code)
    {
        while (code.peek() == ' ') code.ignore();
        char c = code.peek();
        if (isalpha(c) || c == '_')
        {
            ctoken = ID;
            buffer = make_id();
        }
        else if (isdigit(c))
        {
            ctoken = NUM;
            buffer = make_number();
        }
        else if ((c == '"' || c == '\''))
        {
            ctoken = STR;
            buffer = make_string();
        }
        else if (is_symbol(c))
        {
            ctoken = Token(c);
            buffer = c;
            code.ignore();
        }
        else
        {
            ctoken = EXIT;
            buffer = "__EXIT__";
        }
    }
    else
    {
        ctoken = EXIT;
        buffer = "__END_OF_CODE__";
    }
    return ctoken;
}
