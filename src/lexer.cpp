#include "../headers/Lexer.hpp"
#include "consts.hpp"
#include <cctype>


bool Lexer::is_identifier(char c) const { return std::isalnum(c) || c == '_'; }
bool Lexer::is_number_char(char c) const { return (std::isdigit(c) || c == '.' || c == '-' || c == '_'); }
bool Lexer::is_symbol(char c) const { return symbols.contains(c); }
bool Lexer::is_operator(std::string str) const { return operators.contains(str); }


bool Lexer::is_potential_operator(char c) const
{
    bool pot_op = false;
    for (auto op : operators) pot_op |= op.first.starts_with(c);
    return pot_op;
}


bool Lexer::is_potential_operator(std::string str) const
{
    bool pot_op = false;
    for (auto op : operators) pot_op |= op.first.starts_with(str);
    return pot_op;
}


NumLitToken* Lexer::make_number()
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

    return new NumLitToken(num);
}


IdentifierToken* Lexer::make_identifier()
{
    char curr = code.peek();
    std::string id = "";
    while ((is_identifier(curr)) && code.get(curr)) id += curr;
    return new IdentifierToken(id);
}


OperatorToken* Lexer::make_operator()
{
    char curr = code.peek();
    std::string op = {};
    do op += curr; while (code.get(curr) && is_potential_operator(op) && !(is_operator(op + (char)code.peek())));
    // if adding the next char coul make op an operator, add it to op, otherwise break
    return new OperatorToken(op);
}


SymbolToken* Lexer::make_symbol()
{
    return new SymbolToken(std::string(1, code.get()));
}


bool Lexer::next_token(Token* tok)
{
    if (code)
    {
        char curr = code.peek();
        if (is_identifier(curr))
        {
            tok = make_identifier();
        }
        else if (is_operator(std::string(1, curr)))
        {
            tok = make_operator();
        }
        else if (is_number_char(curr))
        {
            tok = make_number();
        }
        else if (is_symbol(curr))
        {
            tok = make_symbol();
        }
        else throw -2;
        return true;
    }
    else return false;
}


Lexer::Lexer(std::stringstream& input) : code(std::move(input))
{
    ;
}
