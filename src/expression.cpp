#include "expression.hpp"
#include "error.hpp"


ExprPtr::ExprPtr(const ExprPtr& other) noexcept
{
    destroy();
    expr = (other.expr == nullptr) ? nullptr : new _Expr_(*other.expr);
}


ExprPtr::ExprPtr(ExprPtr&& other) noexcept
{
    expr = other.expr;
    other.expr = nullptr;
}


ExprPtr& ExprPtr::operator=(const ExprPtr& other) noexcept
{
    if (this == &other) return *this;
    destroy();
    expr = (other.expr == nullptr) ? nullptr : new _Expr_(*other.expr);
    return *this;
}


ExprPtr& ExprPtr::operator=(ExprPtr&& other) noexcept
{
    if (this == &other) return *this;
    expr = other.expr;
    other.expr = nullptr;
    return *this;
}


void ExprPtr::add(const ExprPtr& arg)
{
    if (is_null()) throw err::ExprError("called ExprPtr::add with a nullptr expr");
    expr->add(arg);
}


bool ExprPtr::is_null() const
{
    return (expr == nullptr);
}


bool ExprPtr::terminates() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::terminates with a nullptr expr");
    return expr->terminates();
}


Token ExprPtr::token() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::token with a nullptr expr");
    return expr->token;
}


ExprPtr ExprPtr::left() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::terminates with a nullptr expr");
    return expr->left;
}


ExprPtr ExprPtr::right() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::right with a nullptr expr");
    return expr->right;
}


std::string ExprPtr::value() const
{
    if (is_null()) throw err::ExprError("called ExprPtr::value with a nullptr expr");
    return expr->value;
}


void ExprPtr::set_left(const ExprPtr& arg)
{
    if (is_null()) throw err::ExprError("called ExprPtr::set_left with a nullptr expr");
    expr->left = arg;
}


void ExprPtr::set_right(const ExprPtr& arg)
{
    if (is_null()) throw err::ExprError("called ExprPtr::set_left with a nullptr expr");
    expr->right = arg;
}


void ExprPtr::set_value(const std::string& val)
{
    if (is_null()) throw err::ExprError("called ExprPtr::set_value with a nullptr expr");
    expr->value = val;
}


/* %%%%%%%%% cout overload %%%%%%%%% */


std::ostream& operator<<(std::ostream& out, ExprPtr in)
{
    if (!in.is_null())
    {
        out << in.value();
        if (!in.left().is_null()) out << in.left();
        if (!in.right().is_null()) out << in.right();
    }
    return out;
}


/* %%%%%%%%%% _EXPR_ DEFS %%%%%%%%%% */


bool _Expr_::entrance_made = false;


_Expr_::_Expr_(const Token& tok)
    : token(tok)
{
    switch (token) // any fallthrough is intentional for matching
    {
        case NUM:
        case ID:
            throw err::ExprError("identifier with no identifier found somehow");
        case EXIT:
            value = "__EXIT__";
            break;
        case ENTRY:
            if (entrance_made) throw err::ExprError("application entry can only be made once");
            entrance_made = true;
            value = "__ENTRY__";
            break;
        case EMPTY:
            value = "";
            break;
        default:
            value = (char)token;
    }
}


_Expr_::_Expr_(const Token& tok, std::string val)
    : token(tok), value(val)
{
    ;
}


_Expr_::_Expr_(const Token& tok, char c)
    : token(tok), value(1, c)
{
    ;
}


void _Expr_::add(ExprPtr expr)
{
    if (terminates()) throw err::ExprError("expression terminates, but was told to add an expr");
    if (left.is_null()) left = std::move(expr);
    else if (!left.terminates()) left.add(expr);
    else if (right.is_null()) right = std::move(expr);
    else if (!right.terminates() && right.token() != EMPTY) right.add(expr);
    else throw err::ExprError("reached end of _Expr_::add");
}


bool _Expr_::terminates() const
{
    if (token == ID || token == NUM) return true;
    if (left.is_null() || right.is_null()) return false;
    else return (left.terminates() && right.terminates());
}


ExprPtr _Expr_::unary(const Token& token)
{
    ExprPtr expr(token);
    expr.set_right(ExprPtr(EMPTY));
    return expr;
}
