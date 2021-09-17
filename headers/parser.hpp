#ifndef PARSER_HPP
#define PARSER_HPP

#include <sstream>

#include "lexer.hpp"
#include "scope.hpp"
#include "expression.hpp"


class Parser
{
    Lexer lxr;
    Scope scp;
    ExprPtr root = ExprPtr(ENTRY);

    ExprPtr scope();
    ExprPtr assign();
    ExprPtr add();
    ExprPtr mul();
    ExprPtr cmp();
    ExprPtr eq();
    ExprPtr _xor();
    ExprPtr _or();
    ExprPtr _and();
    ExprPtr unary();
    ExprPtr terminal();

    public:
    Parser(std::stringstream& input) : lxr(input), scp() { }
    ExprPtr operator()();
};

#endif