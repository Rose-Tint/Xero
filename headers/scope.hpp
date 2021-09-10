#pragma once

#include <unordered_set>
#include <cstdint>
#include "expression.hpp"


class Scope
{
    unsigned char level;
    std::unordered_set<std::uint16_t> functions;
    std::unordered_set<std::string> vars;
    std::unordered_set<std::string> user_types;

public:
    void add_var(std::string);
    void add_fn(...);
    void add_struct(std::string);

    bool contains(expr_t);
    Scope(const Scope&);
};
