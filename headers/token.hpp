#pragma once

#include <string>


typedef unsigned char id_t;


struct Token
{
    virtual constexpr id_t id() const;

    explicit Token(std::string);

    const std::string value;
};


struct IdentifierToken final : Token
{
    virtual constexpr id_t id() const override;
};


struct SymbolToken : Token
{
    virtual constexpr id_t id() const override;
};


struct SeperatorToken final : SymbolToken
{
    virtual constexpr id_t id() const override;
};


struct KeywordToken final : Token
{
    virtual constexpr id_t id() const override;
};


struct OperatorToken final : Token
{
    virtual constexpr id_t id() const override;
};


struct LiteralToken : Token
{
    virtual constexpr id_t id() const override;
};


struct NumLitToken final : LiteralToken
{
    virtual constexpr id_t id() const override;
};


struct StrLitToken final : LiteralToken
{
    virtual constexpr id_t id() const override;
};
