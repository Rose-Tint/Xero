#include "headers/expression.hpp"


expr_t expr_t::operator=(const expr_t& other)
{
    expr_t expr(other);
}


expr_t::expr_t(const expr_t& other)
{
    *left = other.left;
    *right = other.right;
    type = other.type;
    token = other.token;
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


void expr_t::add(expr_t expr)
{
    if (token.is_final()) // base case
    {
        return;
    }
    else if (token.type == BIOP || token.type == ENCAP)
    {
        if (left == nullptr) *left = expr;
        else if (left->is_final())
        {
            if (right == nullptr) *right = expr;
            else right->add(expr);
        }
        else left->add(expr);
    }
    else if (token.type == UNOP || token.type = KEYWORD)
    {
        if (left == nullptr) *left = expr;
        else left->add(expr);
    }
    else throw -2;
}
