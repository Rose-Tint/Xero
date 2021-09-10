#pragma once

#include <string>


enum TokenType
{
    IDENTIFIER,
    KEYWORD,
    ENCAP,
    ENDL,
    UNOP,
    BIOP,
    LITERAL
};


struct token_t
{
    const TokenType type;
    const std::string value;
    bool is_final() const { return (type == IDENTIFIER) || (type == LITERAL); }
    token_t operator=(const token_t&);
};


token_t token_t::operator=(const token_t& other)
{
    token_t copy { other.type, other.value };
    return copy;
}
