#include "scope.hpp"


void Scope::operator--(int)
{
    decltype(names) replacement = names;
    for (auto var : names) if (var.second.level == level) replacement.erase(var.first);
    names = std::move(replacement);
    level--;
}
