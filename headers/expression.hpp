#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <iostream>
#include <string>

#include "token.hpp"


class _Expr_;


// RAII/smart pointer wrapper for _Expr_
class ExprPtr
{
    friend std::ostream& operator<<(std::ostream&, ExprPtr&);
    void destroy() noexcept { delete expr; expr = nullptr; }

    _Expr_* expr;

    public:
    ExprPtr() noexcept : expr(nullptr) { }
    explicit ExprPtr(const Token& tok) noexcept : expr(new _Expr_(tok)) { }
    explicit ExprPtr(const Token& tok, std::string str) noexcept : expr(new _Expr_(tok, str)) { }
    explicit ExprPtr(const Token& tok, char c) noexcept : expr(new _Expr_(tok, c)) { }

    ExprPtr(const ExprPtr&) noexcept;
    ExprPtr(ExprPtr&&) noexcept;
    ExprPtr& operator=(const ExprPtr&) noexcept;
    ExprPtr& operator=(ExprPtr&&) noexcept;

    ~ExprPtr() { delete expr; }

    // forwarding _Expr_ methods safely
    void add(const ExprPtr&);
    bool is_null() const;
    bool terminates() const;

    // getters
    Token token() const;
    ExprPtr left() const;
    ExprPtr right() const;
    std::string value() const;

    // setters
    void set_left(const ExprPtr&);
    void set_right(const ExprPtr&);
    void set_value(const std::string&);
};


class _Expr_
{
    friend class ExprPtr;
    static bool entrance_made;

    Token token;
    std::string value;
    ExprPtr left;
    ExprPtr right;

    _Expr_() : token(EMPTY) { }
    explicit _Expr_(const Token&);
    explicit _Expr_(const Token&, std::string);
    explicit _Expr_(const Token&, char);
    _Expr_(const _Expr_&) = default;
    _Expr_(_Expr_&&) = default;
    _Expr_& operator=(const _Expr_&) = default;
    _Expr_& operator=(_Expr_&&) = default;

    void add(ExprPtr);
    bool terminates() const;

    public:
    static ExprPtr unary(const Token&);
    _Expr_() = delete;
};

#endif