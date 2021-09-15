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

    Token make_number();
    Token make_identifier();
    Token make_symbol();

    public:
    Lexer(std::stringstream&);
    Token next();
    Token get();
};
