#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <memory>
#include <iostream>
#include <cstddef>
#include <string>

#include "token.hpp"


class Expr
{
    friend std::ostream& operator<<(std::ostream&, Expr&);
    static bool entrance_made;
    Token token;
    std::string value;
    Expr* left = nullptr;
    Expr* right = nullptr;

    void mov(Expr&&);
    void cpy(const Expr&);

    unsigned int depth() const;

    public:
    Expr() : token(EMPTY) { }
    explicit Expr(Token);
    explicit Expr(Token, std::string);
    explicit Expr(Token, char);

    Expr& operator=(Expr&&);
    Expr& operator=(const Expr&);

    Expr(Expr&& other) { mov(std::move(other)); }
    Expr(const Expr& other) { cpy(other); }

    ~Expr() { delete left; delete right; }

    static Expr* unary(Token);

    void add(Expr*);
    void add(Expr&);
    bool terminates() const;
    std::string get_value() const { return value; }
};

#endif