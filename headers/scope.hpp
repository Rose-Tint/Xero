#pragma once

#include <unordered_map>
#include <cstdint>
#include "expression.hpp"


typedef unsigned char level_t;


class Scope
{
    unsigned char level;
    std::unordered_map<std::uint16_t, level_t> functions;
    std::unordered_map<std::string, level_t> vars;
    std::unordered_map<std::string, level_t> user_types;

public:
    void add_var(std::string);
    void add_fn(); // need to figure out what the params should be
    void add_struct(std::string);

    void level_up();
    void level_down();

    bool contains(Expr*);
    Scope(const Scope&);
};
