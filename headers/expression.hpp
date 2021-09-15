#pragma once

#include <memory>
#include <vector>
#include <cstddef>
#include <string>

#include "token.hpp"


class Expr
{
    Token token;
    std::string value;
    Expr* left = nullptr;
    Expr* right = nullptr;

    public:
    explicit Expr(Token);
    Expr(Token, std::string);
    Expr(Token, char);
    Expr& operator=(Expr&&);
    ~Expr() { delete left; delete right; }

    static Expr unary(Token);

    Expr(const Expr&) = delete;
    Expr& operator=(const Expr&) = delete;
    Expr(Expr&&) = delete;

    void add(Token, std::string);
    void add(Expr&&);
    bool terminates() const;
};
