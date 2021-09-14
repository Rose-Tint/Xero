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
    Expr* get_operating_expr() const;

    public:
    Parser(std::stringstream&);
    BlockExpr* operator()();
};
