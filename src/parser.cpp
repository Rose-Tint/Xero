#include "parser.hpp"


Expr Parser::scope()
{
    Expr expr(LBRACE);
    scp++;
    while (lxr.get() != RBRACE) expr.add(assign());
    scp--;
    return expr;
}


Expr Parser::assign()
{
    Token tok = lxr.get();
    Expr expr = add();
    if (lxr.get() == ASN)
    {
        expr.add(Expr(ASN));
        if (tok != ID) throw 2;
        std::string id = lxr.get_val();
        expr.add(Expr(ID, id));
        lxr.next();
        expr.add(add());
        scp.add(id, lxr.get_val());
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
            default:
                return expr;
        }
    }
}


Expr Parser::eq()
{
    Expr expr = _xor();
    while (1)
    {
        Token token = lxr.get();
        if (token == EQ)
        {
            expr.add(Expr(token));
            lxr.next();
            expr.add(_xor());
        }
        else return expr;
    }
}


Expr Parser::_xor()
{
    Expr expr = _or();
    while (1)
    {
        Token token = lxr.get();
        if (token == XOR)
        {
            expr.add(Expr(token));
            lxr.next();
            expr.add(_or());
        }
        else return expr;
    }
}


Expr Parser::_or()
{
    Expr expr = _and();
    while (1)
    {
        Token token = lxr.get();
        if (token == OR)
        {
            expr.add(Expr(token));
            lxr.next();
            expr.add(_and());
        }
        else return expr;
    }
}


Expr Parser::_and()
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
            case (NOT):{
                Expr unary = Expr::unary(token);
                lxr.next();
                unary.add(terminal());
                expr.add(unary);
            } break;
            default:
                return expr;
        }
    }
}


Expr Parser::terminal()
{
    std::string arg_s = lxr.get_val();
    Expr expr;
    Token token = lxr.get();
    lxr.next();
    switch (token)
    {
        case ID:
            expr = Expr(token, scp[arg_s].value);
            break;
        case NUM:
            expr = Expr(token, arg_s);
            break;
        case LPAREN:
            expr = add();
            if (token != RPAREN) throw 2;
            break;
        /*case LBRACE:
            expr = scope();
            if (lxr.get() != RBRACE) throw 2;
            break;*/ // i dont THINK this is right
        case ENDL:
            expr = assign();
            break;
        default:
            throw 2;
    }
    return expr;
}


Expr Parser::operator()()
{
    return root;
}
