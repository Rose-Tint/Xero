#include "headers/expression.hpp"
#include <algorithm>


expr_t expr_t::operator=(const expr_t& other)
{
    expr_t new_other = other;
    return new_other;
}


expr_t::expr_t(token_t tok) : token(tok) {}


expr_t::expr_t(token_t tok, expr_t left_) : token(tok)
{
    *left = left_;
}


expr_t::expr_t(token_t tok, expr_t left_, expr_t right_) : token(tok)
{
    *left = left_;
    *right = right_;
}
