#include "expression.hpp"


Expr::Expr(Token tok)
    : token(tok)
{
    switch (token) // any fallthrough is intentional for matching
    {
        case NUM:
        case STR:
        case ID:
            throw 3;
        case EXIT:
            value = "__EXIT__";
            break;
        case ENTRY:
            value = "__ENTRY__";
            break;
        case EMPTY:
            value = "";
            break;
        default:
            value = (char)token;
    }
}


Expr Expr::unary(Token token)
{
    Expr expr = Expr(token);
    expr.right = new Expr(EMPTY);
    return expr;
}


Expr::Expr(Token tok, std::string val)
    : token(tok), value(val)
{
    ;
}


Expr::Expr(Token tok, char c)
    : token(tok), value(1, c)
{
    ;
}


Expr& Expr::operator=(Expr&& other)
{
    if (this == &other) return *this;
    left = other.left;
    right = other.left;
    token = other.token;
    value = other.value;
    other.left = nullptr;
    other.right = nullptr;
    other.token = 0;
    other.value = "";
    return *this;
}


void Expr::add(Token tok, std::string val)
{
    if (left == nullptr) left = new Expr(tok, val);
    else if (!left->terminates()) left->add(Token, val);
    else if (right == nullptr) right = new Expr(tok, val);
    else if (!right->terminates() && right->token != EMPTY) right->add(Token, val);
    else throw 3;
}


void Expr::add(Expr&& expr)
{
    if (left == nullptr) *left = expr;
    else if (!left->terminates()) left->add(expr);
    else if (right == nullptr) *right = expr;
    else if (!right->terminates() && right->token != EMPTY) right->add(expr);
    else throw 3;
}


bool Expr::terminates() const
{
    if (token == TERMINAL) return true;
    if (left == nullptr || right == nullptr) return false;
    else return (left->terminates() && right->terminates());
}



