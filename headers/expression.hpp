#pragma once

#include "token.hpp"


class expr_t
{
    token_t token;
    expr_t* left = nullptr;
    expr_t* right = nullptr;
    expr_t(const expr_t&) = default;
    expr_t operator=(const expr_t& other);

    public:
    ~expr_t();
    expr_t(token_t);
    expr_t(token_t, expr_t);
    expr_t(token_t, expr_t, expr_t);
    void add(expr_t);
    bool is_final() const;
    bool is_bottom() const;
};
