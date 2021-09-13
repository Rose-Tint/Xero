#pragma once

#include "expression.hpp"


struct Statement { };

struct Block : Statement
{
    protected:
    Scope scp;
    // Statement** statements;
};

struct Loop : Block { };

struct While : Loop
{
    protected:
    Expr* condition;
};

struct For : Loop
{
    protected:
    Statement* before;
    Statement* each;
};

struct If : Block
{
    protected:
    Expr* condition;
};

struct Else : Block { };
struct Declaration : Statement { };
