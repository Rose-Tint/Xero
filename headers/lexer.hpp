#pragma once

#include <sstream>
#include <memory>

#include "token.hpp"


class Lexer
{
    std::stringstream code;

    bool is_identifier(char) const;
    bool is_number_char(char) const;
    bool is_symbol(char) const;
    bool is_potential_operator(char) const; // is at least the start of an operator
    bool is_potential_operator(std::string) const;
    bool is_operator(std::string) const;

    NumLitToken* make_number();
    IdentifierToken* make_identifier();
    OperatorToken* make_operator();
    SymbolToken* make_symbol();

    public:
    Lexer(std::stringstream&);
    bool next_token(Token*);
};
