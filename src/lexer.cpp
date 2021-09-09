#include "../headers/Lexer.hpp"
#include <cctype>
#include <unordered_set>


bool Lexer::is_operator(char c) { return operators.contains(c); }
bool Lexer::is_identifier(char c) { return std::isalnum(c) || c == '_'; }
bool Lexer::is_number_char(char c) { return (std::isdigit(c) || c == '.' || c == '-' || c == '_'); }
bool Lexer::is_symbol(char c) { return symbols.contains(c); }


token_t Lexer::make_number()
{
    char curr = code.peek();
    std::string num = "";
    while (is_number_char(curr) && code.get(curr))
    {
        if (curr != '_')
        {
            num += curr;
        }
    }

    return { TokenType::LITERAL, num };
}


token_t Lexer::make_identifier()
{
    char curr = code.peek();
    std::string id = "";
    while ((is_identifier(curr)) && code.get(curr))
    {
        id += curr;
    }

    return { TokenType::IDENTIFIER, id };
}


token_t Lexer::make_operator()
{
    char curr = code.peek();
    std::string op = "";
    while (is_operator(curr) && code.get(curr))
    {
        op += curr;
    }

    return { TokenType::OPERATOR, op };
}


token_t Lexer::make_symbol()
{
    char curr = code.peek();
    std::string sym = "";
    while (is_operator(curr) && code.get(curr))
    {
        sym += curr;
    }

    return { TokenType::SYMBOL, sym };
}


token_t Lexer::next()
{
    char curr = code.peek();
    if (is_identifier(curr))
    {
        return make_identifier();
    }
    else if (is_operator(curr))
    {
        return make_operator();
    }
    else if (is_number_char(curr))
    {
        return make_number();
    }
    else if (is_symbol(curr))
    {
        return make_symbol();
    }
    else throw -2;
}


Lexer::Lexer(std::stringstream input)
{
    input.swap(code);
}
