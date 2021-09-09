#pragma once

#include <sstream>
#include <unordered_set>
#include <vector>
#include "token.hpp"


class Lexer
{
    const std::unordered_set<char> symbols { ';',':','{','}','[',']','(',')' };
    const std::unordered_set<char> operators { '@','+','-','=','*','/','%','<','>','|','&','^',',','!','#','?' };
    std::stringstream code;
    bool is_operator(char);
    bool is_identifier(char);
    bool is_number_char(char);
    bool is_symbol(char);
    token_t make_number();
    token_t make_identifier();
    token_t make_operator();
    token_t make_symbol();

    public:
    Lexer(std::stringstream);
    token_t next_token();
    bool next_token(token_t&)
    std::vector<token_t> next_statement();
};
