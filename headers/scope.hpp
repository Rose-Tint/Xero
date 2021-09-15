#pragma once

#include <map>
#include <pair>
#include <string>

#include "token.hpp"
#include "expression.hpp"


typedef char level_t;


class Scope
{
    using std::pair, std::map, std::string;
    protected:
    level_t level = 0;
    map<string, string, level_t> names;

    public:
    Scope() = default;
    void add(string, string);
    void operator++(int) { level++; }
    void operator--(int);
    std::string operator[](std::string key) { return names }
};
