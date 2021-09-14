#pragma once

#include <sstream>

#include "expression.hpp"
#include "lexer.hpp"
#include "scope.hpp"


class Parser
{
    Lexer lxr;
    Expr* root;
    Scope scp;

    public:
    Parser(std::stringstream&);
    Expr* operator()();
};
