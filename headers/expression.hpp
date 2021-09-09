#pragma once

#include "token.hpp"


struct expr_t;


typedef expr_t *ExprNode;


class expr_t
{
    token_t token;
    ExprNode left = nullptr;
    ExprNode right = nullptr;

    public:
    expr_t operator=(const expr_t&);
    expr_t(token_t tok);
    expr_t(token_t tok, expr_t left_);
    expr_t(token_t tok, expr_t left_, expr_t right_);
    ExprNode get_left() const { return left; }
    ExprNode get_right() const { return right; }
    token_t get_token() const { return token; }
    bool is_bottom() const { return (left == nullptr) && (right == nullptr); }
};
