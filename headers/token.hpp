#pragma once

#include <string>


enum token_id_t : unsigned char
{
    TOKEN,
    IDENTIFIER,
    KEYWORD,
    SYMBOL,
    SEP,
    OPERATOR,
    BINARY_OP,
    UNARY_OP,
    LITERAL,
    NUMBER,
    STR_LIT
};


struct Token
{
    virtual constexpr token_id_t id() const { return TOKEN; };

    explicit Token(const std::string& str) : value(str) {}

    virtual Token* clone() const { return new Token(*this); }

    const std::string value;
};


struct IdentifierToken final : Token
{
    IdentifierToken(const std::string& str) : Token(str) { }
    virtual constexpr token_id_t id() const override { return IDENTIFIER; }
    virtual IdentifierToken* clone() const { return new IdentifierToken(*this); }
};


struct SymbolToken : Token
{
    SymbolToken(const std::string& str) : Token(str) { }
    virtual constexpr token_id_t id() const override { return SYMBOL; }
    virtual SymbolToken* clone() const { return new SymbolToken(*this); }
};


struct SeperatorToken final : SymbolToken
{
    SeperatorToken(const std::string& str) : SymbolToken(str) { }
    virtual constexpr token_id_t id() const override { return SEP; }
    virtual SeperatorToken* clone() const { return new SeperatorToken(*this); }
};


struct KeywordToken final : Token
{
    KeywordToken(const std::string& str) : Token(str) { }
    virtual constexpr token_id_t id() const override { return KEYWORD; }
    virtual KeywordToken* clone() const { return new KeywordToken(*this); }
};


struct OperatorToken : Token
{
    OperatorToken(const std::string& str) : Token(str) { }
    virtual constexpr token_id_t id() const override { return OPERATOR; }
    virtual OperatorToken* clone() const { return new OperatorToken(*this); }
};


struct BinaryOpToken final : OperatorToken
{
    BinaryOpToken(const std::string& str) : OperatorToken(str) { }
    virtual constexpr token_id_t id() const override { return BINARY_OP; }
    virtual BinaryOpToken* clone() const { return new BinaryOpToken(*this); }
};


struct UnaryOpToken final : OperatorToken
{
    UnaryOpToken(const std::string& str) : OperatorToken(str) { }
    virtual constexpr token_id_t id() const override { return UNARY_OP; }
    virtual UnaryOpToken* clone() const { return new UnaryOpToken(*this); }
};


struct LiteralToken : Token
{
    LiteralToken(const std::string& str) : Token(str) { }
    virtual constexpr token_id_t id() const override { return LITERAL; }
    virtual LiteralToken* clone() const { return new LiteralToken(*this); }
};


struct NumLitToken final : LiteralToken
{
    NumLitToken(const std::string& str) : LiteralToken(str) { }
    virtual constexpr token_id_t id() const override { return NUMBER; }
    virtual NumLitToken* clone() const { return new NumLitToken(*this); }
};


struct StrLitToken final : LiteralToken
{
    StrLitToken(const std::string& str) : LiteralToken(str) { }
    virtual constexpr token_id_t id() const override { return STR_LIT; }
    virtual StrLitToken* clone() const { return new StrLitToken(*this); }
};

