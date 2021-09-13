#pragma once

#include <unordered_map>
#include <cstdint>
#include "expression.hpp"


typedef unsigned char level_t;


class Scope
{
    level_t level;
    std::unordered_map<std::uint16_t, level_t> functions;
    std::unordered_map<std::std::string, level_t> names;
    std::unordered_map<Var, level_t> vars;
    std::unordered_map<Type, level_t> user_types;

    public:
    void add_var(DeclaratorExpr*);
    void add_fn(DeclaratorExpr*);
    void add_struct(DeclaratorExpr*);

    void level_up();
    void level_down();

    bool contains(Token*);
    Scope(const Scope&);
};
