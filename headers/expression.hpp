#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <iostream>
#include <string>

#include "token.hpp"


class _Expr_;


// RAII/smart pointer wrapper for _Expr_
class ExprPtr
{
    friend std::ostream& operator<<(std::ostream&, ExprPtr);

    void destroy() noexcept;

    _Expr_* expr;

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
};


const ExprPtr& nullexpr = ExprPtr();


#ifdef X_TESTS
#include <type_traits>
namespace tst
{
#ifndef TESTERROR
#define TESTERROR
class TestError {};
#else
class TestError;
#endif
    bool operator==(const ExprPtr& l, const ExprPtr& r);

    template<class G, class E = G>
    bool check(const G& given, const E& exp);

    template<class E, class R, class ...A>
    bool throws_e(R (*)(A...), A...);

    template<Token, Token, Token>
    bool test_ExprPtr(std::string = "ROOT_ARG", std::string = "LEFT_ARG", std::string = "RIGHT_ARG");
}
#endif
#endif