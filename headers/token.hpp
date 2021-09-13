#pragma once

#include <string>


typedef unsigned char token_id_t;


struct Token
{
    virtual constexpr token_id_t id() const;

    explicit Token(std::string);

    virtual Token* clone() const { return new Token(*this); }

    const std::string value;
};

