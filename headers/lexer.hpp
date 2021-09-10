#pragma once

#include <sstream>
#include <unordered_set>
#include <vector>
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

    token_t make_number();
    token_t make_identifier();
    token_t make_operator();
    token_t make_symbol();

    public:
    Lexer(std::stringstream&);
    token_t next_token();
    bool next_token(token_t&);
    std::vector<token_t> next_statement();
};
