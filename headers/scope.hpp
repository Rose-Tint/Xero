#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

#include "token.hpp"


typedef unsigned char level_t;


class Scope
{
    level_t level;
    std::unordered_map<std::uint16_t, level_t> functions;
    std::unordered_map<std::string, level_t> names;

public:
    // void add_var(DeclaratorExpr*);
    // void add_fn(DeclaratorExpr*);
    // void add_struct(DeclaratorExpr*);
    void level_up();
    void level_down();
    bool contains(Token*) const;
};
