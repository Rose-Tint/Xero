#ifndef LEXER_HPP
#define LEXER_HPP

#include <sstream>
#include <memory>

#include "token.hpp"


class Lexer
{
    std::stringstream& code;
    Token ctoken;
    std::string buffer;

    bool is_identifier(char c) const { return isalnum(c) || c == '_'; }
    bool is_number_char(char c) const { return isdigit(c) || c == '.'; }
    bool is_symbol(char) const;

    std::string make_number();
    std::string make_identifier();

    public:
    Lexer(std::stringstream&);
    Token get() const { return ctoken; }
    std::string get_val() const { return buffer; }
    Token next();
};

#endif