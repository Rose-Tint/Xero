#include "scope.hpp"


void Scope::add(std::string key, std::string val)
{
    ValueHolder value { val, level };
    names[key] = std::move(value);
}


void Scope::operator--(int)
{
    decltype(names) replacement = names;
    for (auto var : names) if (var.second.level == level) replacement.erase(var.first);
    names = std::move(replacement);
    level--;
}
