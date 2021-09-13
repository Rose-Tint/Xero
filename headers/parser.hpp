#pragma once

#include <sstream>
#include "expression.hpp"
#include "lexer.hpp"


class Parser
{
    Lexer lxr;
    Expr* ast;

    public:
    Parser(std::stringstream);
    Expr* operator()();
};
