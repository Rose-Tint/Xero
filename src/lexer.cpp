#include "../headers/Lexer.hpp"
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
    std::string op = {};
    do op += curr; while (code.get(curr) && is_potential_operator(op) && !(is_operator(op + (char)code.peek())));
    // if adding the next char coul make op an operator, add it to op, otherwise break
    return { operators.at(op), op };
}


token_t Lexer::make_symbol()
{
    char sym = code.get();
    return { symbols.at(sym), std::string(1, sym) };
}


token_t Lexer::next_token()
{
    if (code)
    {
        char curr = code.peek();
        if (is_identifier(curr))
        {
            return make_identifier();
        }
        else if (is_operator(std::string(1, curr)))
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
    else throw -3;
}


bool Lexer::next_token(token_t& tok)
{
    tok = next_token();
    return (bool)code;
}


std::vector<token_t> Lexer::next_statement()
{
    char curr = code.peek();
    token_t token = next_token();
    std::vector<token_t> tokens { token };
    while (token.type != ENDL && code.get(curr))
    {
        token = next_token();
        tokens.push_back(token);
    }
    return tokens;
}


Lexer::Lexer(std::stringstream& input) : code(std::move(input))
{
    ;
}
