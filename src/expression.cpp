#include "headers/expression.hpp"


expr_t expr_t::operator=(const expr_t& other)
{
    expr_t expr(other);
    return expr;
}


expr_t::expr_t(token_t tok) : token(tok)
{
    ;
}


expr_t::expr_t(token_t tok, expr_t left_) : token(tok)
{
    left = new expr_t(left_);
}


expr_t::expr_t(token_t tok, expr_t left_, expr_t right_) : token(tok)
{
    left = new expr_t(left_);
    right = new expr_t(right_);
}


expr_t::~expr_t()
{
    delete left;
    delete right;
}


bool expr_t::is_bottom() const
{
    return ((left == nullptr) && (right == nullptr));
}

bool expr_t::is_final() const
{
    if (token.is_final())
    {
        return true;
    }
    else if (left == nullptr || right == nullptr)
    {
        return false;
    }
    else
    {
        return ((left == nullptr) ? false : left->is_final()) && ((left == nullptr) ? false : right->is_final());
    }
}


unsigned int expr_t::get_depth() const
{
    if (is_bottom()) return 1;
    else if (left == nullptr) return right->get_depth();
    else if (right == nullptr) return left->get_depth();
    else return left->get_depth() + right->get_depth();
}
