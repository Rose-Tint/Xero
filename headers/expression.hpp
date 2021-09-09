#pragma once

#include "token.hpp"


class expr_t
{
    token_t token;
    expr_t* left = nullptr;
    expr_t* right = nullptr;
    expr_t(const expr_t&);

    public:
    ~expr_t();
    expr_t(token_t);
    expr_t(token_t, expr_t);
    expr_t(token_t, expr_t, expr_t);
    expr_t* get_left() const { return left; }
    expr_t* get_right() const { return right; }
    token_t get_token() const { return token; }
    void add(expr_t);
    bool is_final() const;
    bool is_bottom() const;
};
