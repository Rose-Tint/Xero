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
    bool is_final() const;
};


bool token_t::is_final()
{
    return (type == IDENTIFIER) || (type == LITERAL));
}
