#include "scope.hpp"


void Scope::add(string id, string value)
{
    names.insert({ id, value }, level);
}


void Scope::operator--(int)
{
    for (auto var : names) if (var.second == level) names.erase(var.first);
    level--;
}

