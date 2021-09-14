#include "scope.hpp"


Scope& Scope::operator<<(FuncDeclExpr* func)
{
    functions.insert(func->get_signature());
    return *this;
}


Scope& Scope::operator<<(TypeExpr* type)
{
    names.insert({ type->get_name()->get_token()->value, level });
    return *this;
}


Scope& Scope::operator<<(TerminalExpr* identifier)
{
    names.insert({ identifier->get_token()->value, level });
    return *this;
}


void Scope::level_down()
{
    for (auto pair : names) if (pair.second == level) names.erase(pair.first);
    level -= 1;
}

