#pragma once

#include <sstream>

#include "expression.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "scope.hpp"


class Parser
{
    Lexer lxr;
    Scope scp;
    Expr root;

    Expr scope();
    Expr assign();
    Expr add();
    Expr mul();
    Expr cmp();
    Expr eq();
    Expr xor();
    Expr or();
    Expr and();
    Expr unary();
    Expr terminal();

    public:
    Parser(std::stringstream&);
    Expr operator()();
};
