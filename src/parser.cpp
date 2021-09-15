#include "parser.hpp"


Parser::Parser(std::stringstream& input_code)
    : lxr(input_code), scp()
{
    ;
}


Expr Parser::scope()
{
    scp++;
    assign();
    scp--;
}


Expr Parser::assign()
{
    Token tok = lxr.get();
    Expr expr = add();
    if (lxr.get() == ASN)
    {
        expr.add(Expr(ASN));
        if (tok != ID) throw 0;
        std::string id = lxr.buffer;
        expr.add(Expr(ID, id));
        lxr.next();
        expr.add(add());
        scp.add(id, lxr.buffer);
    }
    return expr;
}


Expr Parser::add()
{
    Expr expr = mul();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (PLUS): // intentional fallthrough
            case (MINUS):
                expr.add(Expr(token));
                lxr.next();
                expr.add(mul());
                break;
            default:
                return expr;
        }
    }
}


Expr Parser::mul()
{
    Expr expr = cmp();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (MUL):
            case (DIV):
            case (MOD):
                expr.add(Expr(token));
                lxr.next();
                expr.add(cmp());
                break;
            default:
                return expr;
        }
    }
}


Expr Parser::cmp()
{
    Expr expr = eq();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (LT):
            case (GT):
                expr.add(Expr(token));
                lxr.next();
                expr.add(eq());
                break;
            default return;
        }
    }
}


Expr Parser::eq()
{
    Expr expr = xor();
    while (1)
    {
        Token token = lxr.get();
        if (token == EQ)
        {
            expr.add(Expr(token));
            lxr.next();
            expr.add(xor());
        }
        else return expr;
    }
}


Expr Parser::xor()
{
    Expr expr = or();
    while (1)
    {
        Token token = lxr.get();
        if (token == XOR)
        {
            expr.add(Expr(token));
            lxr.next();
            expr.add(or());
        }
        else return expr;
    }
}


Expr Parser::or()
{
    Expr expr = and();
    while (1)
    {
        Token token = lxr.get();
        if (token == OR)
        {
            expr.add(Expr(token));
            lxr.next();
            expr.add(and());
        }
        else return expr;
    }
}


Expr Parser::and()
{
    Expr expr = unary();
    while (1)
    {
        Token token = lxr.get();
        if (token == AND)
        {
            expr.add(Expr(token));
            lxr.next();
            expr.add(unary());
        }
        else return expr;
    }
}


Expr Parser::unary()
{
    Expr expr = terminal();
    while (1)
    {
        Token token = lxr.get();
        switch (token)
        {
            case (PLUS):
            case (MINUS):
            case (NOT):
                Expr unary = Expr::unary(token);
                lxr.next();
                unary.add(terminal());
                expr.add(unary);
                break;
            default:
                return expr;
        }
    }
}


Expr Parser::terminal()
{
    std::string sval = lxr.buffer;
    Expr expr;
    switch (lxr.get())
    {
        case NUM:
            lxr.next();
            scp[sval];
            break;
        case ID:
            lxr.next();
            break;
        case LPAREN:
            lxr.next();
            add();
            if (lxr.get() != RPAREN) throw 1;
            break;
        case LBRACE:
            lxr.next();
            scope();
            if (lxr.get != RBRACE) throw 2;
            break;
        case ENDL:
            lxr.next()
            assign();
            break;
        default: throw 3;
    }
}
