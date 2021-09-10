#pragma once

#include "token.hpp"


struct Scope;


class expr_t
{
    token_t token;
    expr_t* left = nullptr;
    expr_t* right = nullptr;
    expr_t operator=(const expr_t& other);

    public:
    expr_t(const expr_t&) = default;
    ~expr_t();
    expr_t(token_t);
    expr_t(token_t, expr_t);
    expr_t(token_t, expr_t, expr_t);

    expr_t get_token() const { return token; }
    expr_t* get_left() const { return left; }
    expr_t* get_right() const { return right; }

    void add(expr_t, Scope&);
    bool is_final() const;
    bool is_bottom() const;
    unsigned int get_depth() const;
};
