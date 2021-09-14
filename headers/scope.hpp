#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cstdint>

#include "token.hpp"
#include "expression.hpp"


typedef unsigned char level_t;


class Scope
{
    level_t level = 0;
    std::unordered_set<std::uint16_t> functions;
    std::unordered_map<std::string, level_t> names;

public:
    Scope& operator<<(FuncDeclExpr*); // adds a function to the scope
    Scope& operator<<(TypeExpr*);
    Scope& operator<<(TerminalExpr*);
    void level_up() { level++; }
    void level_down();
    bool contains(Token*) const;
    bool contains(TypeExpr*) const;
    bool contains(FuncDeclExpr*) const;
};
