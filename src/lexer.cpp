#include "lexer.hpp"
#include "error.hpp"


Lexer::Lexer(std::stringstream& input)
    : code(input)
{
    next();
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


std::string Lexer::make_number()
{
    std::string str;
    unsigned int num;
    code >> num;
    str = std::to_string(num);
    if (code.peek() == '.') code >> num;
    str.append(std::to_string(num));
    return str;
}


std::string Lexer::make_identifier()
{
    std::string str;
    char c = code.peek();
    while (code.get(c) && is_identifier(c)) str += c;
    return str;
}


Token Lexer::next()
{
    if (code)
    {
        char c = code.peek();
        if (is_identifier(c))
        {
            ctoken = ID;
            buffer = make_identifier();
        }
        else if (is_number_char(c))
        {
            ctoken = NUM;
            buffer = make_number();
        }
        else if (is_symbol(c))
        {
            ctoken = Token(c);
            buffer = c;
        }
        else if (c == EXIT) ctoken = EXIT;
        else throw err::LexerError(std::string("invalid token"));
    }
    ctoken = EXIT;
    return ctoken;
}
