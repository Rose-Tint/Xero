#pragma once

#include <string>


enum struct TokenType
{
    IDENTIFIER,
    KEYWORD,
    SYMBOL,
    OPERATOR,
    LITERAL
};


struct token_t
{
    const TokenType type;
    const std::string value;
};
