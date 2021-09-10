#pragma once

#include <sstream>
#include "expression.hpp"


class Parser
{
    Lexer lxr;
    expr_t ast;

    public:
    Parser(std::stringstream);
    expr_t& operator()();
};
