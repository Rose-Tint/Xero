#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <iostream>
#include <string>

#include "token.hpp"


namespace tst { class ExprPtrTest; };


class _Expr_;


// RAII/smart pointer wrapper for _Expr_
class ExprPtr
{
    friend std::ostream& operator<<(std::ostream&, ExprPtr);
    friend class tst::ExprPtrTest;

    void destroy() noexcept;

    _Expr_* expr = nullptr;

    public:
    ExprPtr() noexcept;
    explicit ExprPtr(const Token& tok) noexcept;
    explicit ExprPtr(const Token& tok, std::string str) noexcept;
    explicit ExprPtr(const Token& tok, char c) noexcept;

    ExprPtr(const ExprPtr&) noexcept;
    ExprPtr(ExprPtr&&) noexcept;
    ExprPtr& operator=(const ExprPtr&) noexcept;
    ExprPtr& operator=(ExprPtr&&) noexcept;

    ~ExprPtr();

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

    static ExprPtr unary(const Token&);
};


class _Expr_
{
    friend class ExprPtr;
    friend class tst::ExprPtrTest;
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
};


bool operator==(const ExprPtr&, const ExprPtr&);


// const ExprPtr& nullexpr = ExprPtr();
#endif