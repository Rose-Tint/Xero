#pragma once

#include <vector>


struct Statement;
struct Expression;
struct Operator;


struct Statement
{
    ;
};


struct StatementBlock : Statement
{
    std::vector<Statement> statements;
};


struct IfElse : Statement
{
    Expression* condition;
    Statement* if_statement;
    Statement* else_statement;
};


struct WhileLoop : Statement
{
    Expression* condition;
    Statement statement;
};


struct ForLoop : WhileLoop
{
    Statement* before;
    Statement* each;
};


struct VarDecl : Statement
{
    // TODO
};


struct Assignment : Statement
{
    Operator* op;
    // TODO
};


struct VoidFuncCall : Statement
{
    // TODO
};




struct Expression
{
    ;
};


struct BinaryOp : Expression
{
    Operator* op;
    Expression* left;
    Expression* right;
};


struct UnaryOp : Expression
{
    Operator* op;
    Expression* operand;
};


struct FuncCall : Expression
{
    // TODO
};


struct Conditional : Expression
{
    // TODO
};


