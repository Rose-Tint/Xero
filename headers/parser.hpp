#ifndef PARSER_HPP
#define PARSER_HPP

#include <sstream>

#include "expression.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "scope.hpp"


class Parser
{
    Lexer lxr;
    Scope scp;
    Expr* root = new Expr(ENTRY);

    Expr* scope();
    Expr* assign();
    Expr* add();
    Expr* mul();
    Expr* cmp();
    Expr* eq();
    Expr* _xor();
    Expr* _or();
    Expr* _and();
    Expr* unary();
    Expr* terminal();

    public:
    Parser(std::stringstream& input) : lxr(input), scp() { }
    Expr* operator()();
};

#endif